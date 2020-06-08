#include "Sort.hpp"
#include "Change.hpp"

#include <Sort/Sort.hpp>
#include <Sort/Type.hpp>
#include <type_traits>
#include <algorithm>
#include <cassert>
#include <variant>
#include <vector>
#include <tuple>

namespace lab::ui {
namespace {

struct Pair
{
    template<typename K, typename V>
    struct Plain
    {
        using Key = K;
        using Value = V;
    };

    template<typename K, template<typename...> typename V>
    struct Generic
    {
        using Key = K;

        template<typename... Ts>
        using Value = V<Ts...>;
    };
};

namespace detail {

template<typename K, typename V>
constexpr auto is_plain_impl(Pair::Plain<K, V>) -> std::true_type;

template<typename T>
constexpr auto is_plain_impl(T) -> std::false_type;

template<typename T>
constexpr bool is_plain = decltype(is_plain_impl(std::declval<T>()))::value;

template<typename K, template<typename...> typename V>
constexpr auto is_generic_impl(Pair::Generic<K, V>) -> std::true_type;

template<typename T>
constexpr auto is_generic_impl(T) -> std::false_type;

template<typename T>
constexpr bool is_generic = decltype(is_generic_impl(std::declval<T>()))::value;

template<typename T>
constexpr bool is_pair = is_plain<T> || is_generic<T>;

template<typename Pair, typename... Args, typename = std::enable_if_t<detail::is_plain<Pair> && (sizeof...(Args) == 0)>>
constexpr auto value_impl() -> typename Pair::Value;

template<typename Pair, typename... Args, typename = std::enable_if_t<detail::is_generic<Pair> && (sizeof...(Args) > 0)>>
constexpr auto value_impl() -> typename Pair::template Value<Args...>;

template<typename Pair, typename... Args>
using value = decltype(value_impl<Pair, Args...>());

template<typename T, typename... Ts>
constexpr auto index_of_impl() noexcept -> std::size_t
{
    constexpr auto index = [idx = 0] () mutable {
        return ((std::is_same_v<T, Ts> ? false : ++idx) && ...) ? std::size_t(-1) : idx;
    }();

    static_assert(index != std::size_t(-1), "Type not found");
    return index;
}

template<typename T, typename... Ts>
constexpr auto index_of = index_of_impl<T, Ts...>();

} // namespace detail


template<typename... Pairs>
class Map
{
private:
    template<std::size_t I>
    using Pair = std::tuple_element_t<I, std::tuple<Pairs...>>;

public:
    /// TODO: static assert for keys uniqness
    static_assert((detail::is_pair<Pairs> && ...));

    template<typename Key, typename... Args>
    using Get = detail::value<
        Pair<
            detail::index_of<Key, typename Pairs::Key...>
        >,
        Args...
    >;
};

} // namespace

struct Sort::Impl
{
    struct Value {
        struct Int {};

        using Variant = std::variant<
            Int
        >;

        using Map = Map<
            Pair::Plain<Int, int>
        >;
    };

    struct Container {
        struct Vector {};
        struct List {};

        using Variant = std::variant<
            Vector,
            List
        >;

        using Map = Map<
            Pair::Generic<Vector, std::vector>,
            Pair::Generic<List, std::list>
        >;

        static constexpr auto from_string(const std::string_view str) noexcept -> std::optional<Variant>
        {
            if (str == "Vector") {
                return Vector{};
            }

            if (str == "List") {
                return List{};
            }

            return {};
        }
    };

    struct Order {
        struct Asc {};
        struct Desc {};

        using Variant = std::variant<
            Asc,
            Desc
        >;

        using Map = Map<
            Pair::Plain<Asc, std::less<>>,
            Pair::Plain<Desc, std::greater<>>
        >;

        static constexpr auto from_string(const std::string_view str) noexcept -> std::optional<Variant>
        {
            if (str == "Asc") {
                return Asc{};
            }

            if (str == "Desc") {
                return Desc{};
            }

            return {};
        }
    };

    /// Data to be sorted
    Value::Variant value;
    /// TODO: replace this dirty shit with QVariant & deserialization based on Value::Variant
    std::vector<int> data;
    /// Container to be sorted
    Container::Variant container;
    /// Possible order type
    Order::Variant order;
    /// Algorithm type
    sort::type::Type algorithm;
};

Sort::Sort()
    : QObject{},
      _pimpl{new Impl{}}
{ }

Sort::~Sort() noexcept = default;

void Sort::selectContainerType(const QString type)
{
    const auto container = Impl::Container::from_string(type.toStdString());
    if (!container) {
        /// TODO: notify about inconsistency
        return;
    }

    _pimpl->container = std::move(*container);
}

void Sort::selectOrderType(const QString type)
{
    const auto order = Impl::Order::from_string(type.toStdString());
    if (!order) {
        /// TODO: notify about inconsistency
        return;
    }

    _pimpl->order = std::move(*order);
}

void Sort::selectSortType(const QString type)
{
    const auto algorithm = sort::type::from_string(type.toStdString());
    if (!algorithm) {
        /// TODO: notify about inconsistency
        return;
    }

    _pimpl->algorithm = std::move(*algorithm);
}

void Sort::addValue(const QString value)
{
    _pimpl->data.push_back(value.toInt());
}

QVariantList Sort::execute()
{
    QVariantList result;

    std::visit(
        [&] (auto value) mutable {
            using Value = Impl::Value::Map::template Get<decltype(value)>;

            std::visit(
                [&] (auto value) mutable {
                    using Container = Impl::Container::Map::template Get<decltype(value), Value>;

                    Container container;

                    std::transform(
                        _pimpl->data.begin(),
                        _pimpl->data.end(),
                        std::back_inserter(container),
                        [] (const auto& value) {
                            /// TODO: improve with proper serialization
                            return value;
                        }
                    );

                    const auto order = [&] (const auto& lhs, const auto& rhs) {
                        return std::visit(
                            [&] (auto value) {
                                using Order = Impl::Order::Map::template Get<decltype(value)>;

                                return Order{}(lhs, rhs);
                            },
                            _pimpl->order 
                        );
                    };

                    const auto changes = std::visit(
                        [&] (auto value) {
                            return sort::Sort<decltype(value)>{}(
                                container.begin(),
                                container.end(),
                                order
                            );
                        },
                        _pimpl->algorithm
                    );

                    std::transform(
                        changes.begin(),
                        changes.end(),
                        std::back_inserter(result),
                        [&] (const auto& value) {
                            using It = typename Container::iterator;

                            const auto index = [&] (const auto iterator) {
                                return static_cast<std::size_t>(std::distance(container.begin(), iterator));
                            };

                            return std::visit(
                                [&] (const auto& change) {
                                    using Change = std::remove_cv_t<std::remove_reference_t<decltype(change)>>;

                                    QVariant variant;

                                    if constexpr (std::is_same_v<Change, sort::change::Swap<It>>) {
                                        variant.setValue(
                                            change::Swap{
                                                index(change.first),
                                                index(change.second)
                                            }
                                        );
                                    } else if constexpr (std::is_same_v<Change, sort::change::SelectPivot<It>>) {
                                        variant.setValue(
                                            change::SelectPivot{
                                                index(change.value)
                                            }
                                        );
                                    } else if constexpr (std::is_same_v<Change, sort::change::SelectSubrange<It>>) {
                                        variant.setValue(
                                            change::SelectSubrange{
                                                index(change.first),
                                                index(change.last)
                                            }
                                        );
                                    } else if constexpr (std::is_same_v<Change, sort::change::MergeSubranges<It>>) {
                                        variant.setValue(
                                            change::MergeSubranges{
                                                index(change.first),
                                                index(change.last)
                                            }
                                        );
                                    } else if constexpr (std::is_same_v<Change, sort::change::Compare<It>>) {
                                        variant.setValue(
                                            change::Compare{
                                                index(change.first),
                                                index(change.second)
                                            }
                                        );
                                    } else {
                                        assert(false);
                                    }

                                    return variant;
                                },
                                value
                            );
                        }
                    );
                },
                _pimpl->container
            );        
        },
        _pimpl->value
    );

    return result;
}

void Sort::clear()
{
    _pimpl->data.clear();
}

} // namespace lab::ui
