#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename BidirIt, typename Comp>
constexpr void insertion(BidirIt begin, BidirIt end, Comp comp)
{
    assert(begin <= end && "Invalid range");

    for (; begin != end; ++begin) {
        for (auto it = std::next(begin); it != end; ++it) {
            if (!comp(*begin, *it)) {
                std::iter_swap(begin, it);
            }
        }
    }
}

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename BidirIt>
constexpr void insertion(BidirIt begin, BidirIt end)
{
    insertion(begin, end, std::less<>{});
}

} // namespace lab::sort
