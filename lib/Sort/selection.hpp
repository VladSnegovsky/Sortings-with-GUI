#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason on random access iterators using selection sort.
 */
template<typename Iter, typename Comp>
constexpr void selection(Iter first, Iter last, Comp comp)
{
    for (; first != last; ++first) {
        const auto min = std::min_element(first, last, comp);
        if (min != first) {
            std::iter_swap(min, first);
        }
    }
}

/**
 * @brief Sorts [begin, end) diapason on random access iterators using selection sort.
 */
template<typename Iter>
constexpr void selection(Iter first, Iter last)
{
    selection(first, last, std::less<>{});
}

} // namespace lab::sort
