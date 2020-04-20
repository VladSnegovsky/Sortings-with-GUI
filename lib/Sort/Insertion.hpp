#pragma once

#include <functional>
#include <iterator>
#include <cassert>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename BidirIt, typename Comp = std::less<>>
constexpr void insertion(BidirIt begin, BidirIt end, Comp comp = {})
{
    assert(begin <= end && "Invalid range");

    for (; begin != end; ++begin) {
        for (auto it = std::next(begin); it != end; ++it) {
            if (comp(*begin, *it)) {
                using std::swap;
                swap(*begin, *it);
            }

        }
    }
}

} // namespace lab::sort
