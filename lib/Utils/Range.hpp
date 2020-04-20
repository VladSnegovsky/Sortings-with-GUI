#pragma once

#include <type_traits>
#include <functional>
#include <iterator>

namespace lab::utils {

/**
 * @brief Wrapper around sortable container with automatic notification
 * about changed values.
 * @note Class is owning.
 */
template<typename Container>
class Range
{
public:
    class Iterator
    {
    private:
        using real_type = typename Container::iterator_type;

    public:
        class Value
        {
        private:
            using real_type = typename Container::value_type;

        public:
            constexpr friend void swap(Value& lhs, Value& rhs) noexcept
            {
                using std::swap;
                swap(lhs._value, rhs._value);
            }

            constexpr operator real_type&() noexcept
            {
                return _value;
            }

            constexpr operator const real_type&() const noexcept
            {
                return _value;
            }

        private:
            real_type& _value;
        };


        [[nodiscard]]
        constexpr auto operator*() const noexcept -> Value
        {
            return Value{};
        }

    private:
        real_type& value;
    };

    struct Change
    {

    };

    using change_handler_type = std::function<void(Change)>;


    constexpr explicit Range(Container container) noexcept(
            std::is_nothrow_move_constructible_v<Container>
        ) :
        _container{std::move(container)}
    { }

    void set_change_handler(change_handler_type handler) noexcept(
            std::is_nothrow_move_assignable_v<change_handler_type>
        )
    {
        _handler = std::move(handler);
    }


    [[nodiscard]]
    constexpr auto begin() noexcept
    {
        return Iterator{};
    }

    [[nodiscard]]
    constexpr auto begin() const noexcept
    {
        return Iterator{};
    }

    [[nodiscard]]
    constexpr auto end() noexcept
    {
        return Iterator{};
    }

    [[nodiscard]]
    constexpr auto end() const noexcept
    {
        return Iterator{};
    }

private:
    Container _container;
    change_handler_type _handler;
};

template<typename T>
Range(T) -> Range<T>;

} // namespace lab::utils