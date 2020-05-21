#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

namespace detail {
    
/**
 * @brief Sorts [begin, end) diapason on forward iterators using selection sort.
 */
template<typename FIter, typename Comp>
constexpr void selection(FIter first, FIter last, Comp comparator, std::forward_iterator_tag) {
    while (first != last) {
        auto begin = first;
        while (begin != last) {
            if (comparator(*begin, *first)) {
                std::iter_swap(begin, first);
            }
            std::advance(begin, 1);
        }
        std::advance(first, 1);
    }
}

} // namespace detail

/**
 * @brief Sorts [begin, end) diapason on random access iterators using selection sort.
 */
template<typename Iter, typename Comp>
constexpr void selection(Iter first, Iter last, Comp comparator) {
    detail::selection(first, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
}

/**
 * @brief Sorts [begin, end) diapason on random access iterators using selection sort.
 */
template<typename Iter>
constexpr void selection(Iter first, Iter last) {
    selection(first, last, std::less<>());
}

} // namespace lab::sort
