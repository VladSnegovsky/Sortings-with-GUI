#pragma once

#include <functional>
#include <algorithm>
#include <iterator>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename Iter, typename Comp>
constexpr void insertion(Iter first, Iter last, Comp comp)
{
    for (; first != last; ++first) {
        for (auto it = std::next(first); it != last; ++it) {
            if (!comp(*first, *it)) {
                std::iter_swap(first, it);
            }
        }
    }
}

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename Iter>
constexpr void insertion(Iter first, Iter last)
{
    insertion(first, last, std::less<>{});
}

} // namespace lab::sort
