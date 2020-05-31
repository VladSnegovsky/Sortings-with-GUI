#include "Sort.hpp"
#include "Change.hpp"

#include <Sort/bubble.hpp>
#include <Sort/heap.hpp>
#include <Sort/insertion.hpp>
#include <Sort/merge.hpp>
#include <Sort/quick.hpp>
#include <Sort/selection.hpp>
#include <Utils/Range.hpp>
#include <QDebug>
#include <type_traits>
#include <variant>
#include <vector>

namespace lab::ui {
namespace {

/**
 * @brief Helper to simplify boilerplate typing.
 */
template<typename T, template<typename...> typename... Ts>
using container_variant = std::variant<Ts<T>...>;

/**
 * @brief Alias to help compiler deduce return type.
 */
template<typename Container, typename It = typename Container::iterator>
using function = void(It first, It last);

/**
 * @brief Convert name to 
 */
template<typename Container>
constexpr auto algorithm_from_string(const std::string_view name) noexcept -> function<Container>*
{
    using iterator = typename Container::iterator;

    if (name == "BubbleSort") {
        return sort::bubble<iterator>;
    }

    if (name == "HeapSort") {
        return sort::heap<iterator>;
    }

    if (name == "InsertionSort") {
        return sort::insertion<iterator>;
    }

    if (name == "MergeSort") {
        return sort::merge<iterator>;
    }

    if (name == "QuickSort") {
        return sort::quick<iterator>;
    }

    if (name == "SelectionSort") {
        return sort::selection<iterator>;
    }

    return nullptr;
}

} // namespace

struct Sort::Impl
{
    /// Type used for demonstration
    using value_type = int;

    /// Possible container type
    using container_type = container_variant<
        value_type,
        std::vector
    >;

    /// Container to be sorted
    container_type container;
    /// Algorithm type
    std::string algorithm;
};

Sort::Sort()
    : QObject{},
      _pimpl{new Impl{}}
{ }

Sort::~Sort() noexcept = default;

void Sort::selectType(const QString type)
{
    _pimpl->algorithm = type.toStdString();
}

void Sort::addValue(const QString value)
{
    std::visit([&](auto& container) {
            container.push_back(value.toInt());
        },
        _pimpl->container
    );
}

QVariantList Sort::execute()
{
    QVariantList result;

    std::visit([&](auto& container) {
            utils::Range range{container};

            range.set_change_handler([&] (auto change) mutable {
                const auto index = [&] (const auto it) {
                    return static_cast<std::size_t>(std::distance(container.begin(), it));
                };

                QVariant variant;
    
                variant.setValue(Change{index(change.first), index(change.second)});
                result.push_back(std::move(variant));
            });

            /// Choose sort type
            const auto sort = algorithm_from_string<decltype(range)>(_pimpl->algorithm);
            if (!sort) {
                return;
            }

            /// Invoke sort & aggregate changes
            sort(range.begin(), range.end());
        },
        _pimpl->container
    );

    return result;
}

void Sort::clear()
{
    std::visit([] (auto& container) {
            container.clear();
        },
        _pimpl->container
        );
}

} // namespace lab::ui
