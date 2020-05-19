#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason on forward iterators using quick sort.
 */
template<typename FIter, typename Comp>
constexpr void quick(FIter first, FIter last, Comp comparator, std::forward_iterator_tag) {
    if ((first != last)) {
        auto pivot = first;
        auto mid1 = std::partition(first, last, [&comparator, pivot](const auto &val) {return comparator(val, *pivot);});
        auto mid2 = std::partition(mid1, last, [&comparator, pivot](const auto &val) {return !comparator(*pivot, val);});

        quick(first, mid1, comparator, std::forward_iterator_tag());
        quick(mid2, last, comparator, std::forward_iterator_tag());
    }
}

/**
 * @brief Sorts [begin, end) diapason on random access iterators using quick sort.
 */
template<typename RAIter, typename Comp>
constexpr void quick(RAIter first, RAIter last, Comp comparator, std::random_access_iterator_tag) {
    if ((first != last)) {
        auto pivot = std::next(first, std::distance(first, last)/2);
        auto mid1 = std::partition(first, last, [&comparator, pivot](const auto &val) {return comparator(val, *pivot);});
        auto mid2 = std::partition(mid1, last, [&comparator, pivot](const auto &val) {return !comparator(*pivot, val);});

        quick(first, mid1, comparator, std::random_access_iterator_tag());
        quick(mid2, last, comparator, std::random_access_iterator_tag());
    }
}

/**
 * @brief Sorts [begin, end) diapason using quick sort.
 */
template<typename Iter, typename Comp = std::less<typename std::iterator_traits<Iter>::value_type>>
constexpr void quick(Iter first, Iter last, Comp comparator = Comp()) {
    quick(first, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
}

} // namespace lab::sort
