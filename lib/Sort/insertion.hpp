#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason on forward iterators using insertion sort.
 */
template<typename FIter, typename Comp>
constexpr void insertion(FIter first, FIter last, Comp comparator, std::forward_iterator_tag) {
    if (first == last) {
        return;
    }
    auto left = first;
    auto right = std::next(first);
    while (right != last) {
            auto prev = std::next(first, std::distance(first, right)-1);
            while ((right != first) && (comparator(*right, *prev))) {
                std::iter_swap(right, prev);
                right = prev;
                if (right != first) {
                    prev = std::next(first, std::distance(first, right)-1);
                }
            }
            std::advance(left, 1);
            right = std::next(left);
        }
}

/**
 * @brief Sorts [begin, end) diapason on random access iterators using insertion sort.
 */
template<typename RAIter, typename Comp>
constexpr void insertion(RAIter first, RAIter last, Comp comparator, std::random_access_iterator_tag) {
    if (first == last) {
        return;
    }
    auto left = first;
    auto right = std::next(first);
    while (right != last) {
        while ((right != first) && (comparator(*right, *std::next(right, -1)))) {
            std::iter_swap(right, std::next(right, -1));
            std::advance(right, -1);
        }
        std::advance(left, 1);
        right = std::next(left);
    }
}

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename Iter, typename Comp>
constexpr void insertion(Iter first, Iter last, Comp comparator) {
    insertion(first, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
}

/**
 * @brief Sorts [begin, end) diapason using insertion sort.
 */
template<typename Iter>
constexpr void insertion(Iter first, Iter last) {
    insertion(first, last, std::less<>());
}

} // namespace lab::sort
