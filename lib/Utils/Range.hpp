#pragma once

#include <type_traits>
#include <functional>
#include <iterator>
#include <cassert>
#include <utility>

namespace lab::utils {
namespace detail {

template<typename T, typename = void>
inline constexpr bool is_resizable_v = false;

template<typename T>
inline constexpr bool is_resizable_v<T, std::void_t<
        decltype(&T::resize)
    >> = true;


template<typename T, typename = void>
inline constexpr bool is_contiguous_container_v = false;

template<typename T>
inline constexpr bool is_contiguous_container_v<T, std::void_t<
        decltype(std::declval<T>().data()), 
        decltype(std::declval<T>().size())
    >> = true;


template<typename T, typename = void>
inline constexpr bool has_push_back_v = false;

template<typename T>
inline constexpr auto has_push_back_v<T, std::void_t<
        decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))
    >> = true;


template<typename>
inline constexpr bool dependent_false_v = false;


template<typename NewType, template<typename, typename...> typename Container, typename Type, typename... Args>
constexpr auto wrap_value_impl(Container<Type, Args...>) noexcept -> Container<NewType, Args...>;

template<typename NewType, typename Type, auto Size>
constexpr auto wrap_value_impl(std::array<Type, Size>) noexcept -> std::array<NewType, Size>;

template<typename Type, typename Container>
using wrap_value_t = decltype(wrap_value_impl<Type>(std::declval<Container>()));


template<typename InputIt, typename OutputIt, typename UnaryOp>
constexpr void transform(InputIt first, InputIt last, OutputIt result, UnaryOp unary_op)
{
    for (; first != last; ++first, (void)++result) {
        *result = unary_op(first);
    }
}

} // namespace detail


/**
 * @brief Wrapper around sortable container with automatic notification
 * about swapped values.
 */
template<typename Container>
class Range
{
public:
    struct Change
    { };

    using change_handler_type = std::function<void(Change)>;


    constexpr explicit Range(Container& container)
    {
        if constexpr (detail::is_contiguous_container_v<Container>) {
            if constexpr (detail::is_resizable_v<Container>) {
                _container.resize(std::size(container));
            }

            detail::transform(
                container.begin(),
                container.end(),
                begin(),
                [&] (auto iter) {
                    return Value{iter, &_handler};
                }
            );
        } else if constexpr (detail::has_push_back_v<Container>) {
            detail::transform(
                container.begin(),
                container.end(),
                std::back_inserter(_container),
                [&] (auto iter) {
                    return Value{iter, &_handler};
                }
            );
        } else {
            static_assert(detail::dependent_false_v<Container>,
                         "This type of container can't be wrapped in range");
        }
    }

    void set_change_handler(change_handler_type handler) noexcept(
            std::is_nothrow_move_assignable_v<change_handler_type>
        )
    {
        _handler = std::move(handler);
    }


    [[nodiscard]]
    constexpr auto begin() noexcept
    {
        return _container.begin();
    }

    [[nodiscard]]
    constexpr auto end() noexcept
    {
        return _container.end();
    }

private:
    class Value
    {
    private:
        using iterator = typename Container::iterator;
        using value_type = typename Container::value_type;

    public: 
        constexpr Value() noexcept = default;

        constexpr Value(Value&& that) noexcept
        {
            _iter = that._iter;
            that._iter = {};

            _handler = that._handler;
            that._handler = nullptr;
        }

        Value& operator=(Value&& that) noexcept
        {
            _iter = that._iter;
            that._iter = {};

            _handler = that._handler;
            that._handler = nullptr;

            return *this;
        }

        constexpr friend void swap(Value& lhs, Value& rhs) noexcept
        {
            using std::swap;
            swap(*lhs._iter, *rhs._iter);
        }

        constexpr operator const value_type&() const noexcept
        {
            return *_iter;
        }

    private:
        friend Range;

        constexpr explicit Value(iterator iter, const change_handler_type* handler) noexcept :
            _iter{iter},
            _handler{handler}
        { }

    private:
        iterator _iter;
        const change_handler_type* _handler{nullptr};
    };

private:
    detail::wrap_value_t<Value, Container> _container;
    change_handler_type _handler;
};

template<typename Container>
Range(Container) -> Range<Container>;

} // namespace lab::utils
