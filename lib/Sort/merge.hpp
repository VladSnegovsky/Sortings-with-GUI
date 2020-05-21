#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <forward_list>

namespace lab::sort {

/**
 * @brief Sorts [begin, end) diapason on random access iterators using merge sort.
 */
template<typename RAIter, typename Comp>
constexpr void merge(RAIter first, RAIter last, Comp comparator, std::random_access_iterator_tag) {
    if (std::distance(first, last) > 1) {
        auto middle = std::next(first, std::distance(first, last)/2);
        merge(first, middle, comparator, std::random_access_iterator_tag());
        merge(middle, last, comparator, std::random_access_iterator_tag());
        std::inplace_merge(first, middle, last, comparator);
    }
}

/**
 * @brief Sorts [begin, end) diapason on forward iterators using merge sort.
 */
template<typename FIter, typename Comp>
constexpr void merge(FIter first, FIter last, Comp comparator, std::forward_iterator_tag) {
    if ((first == last) || (std::next(first) == last)) {
        return;
    }
    std::forward_list<typename std::iterator_traits<FIter>::value_type> container;
    for (auto it = first; it != std::next(first, std::distance(first, last)/2); ++it) {
        container.push_front(*std::move(it));
    }
    merge(container.begin(), container.end(), comparator, std::forward_iterator_tag());
    merge(std::next(first, std::distance(first, last)/2), last, comparator, std::forward_iterator_tag());

    std::merge(std::make_move_iterator(container.begin()), std::make_move_iterator(container.end()),
               std::make_move_iterator(std::next(first, std::distance(first, last)/2)), std::make_move_iterator(last), first, comparator);
}

/**
 * @brief Sorts [begin, end) diapason using merge sort.
 */
template<typename Iter, typename Comp>
constexpr void merge(Iter first, Iter last, Comp comparator) {
    merge(first, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
}

/**
 * @brief Sorts [begin, end) diapason using merge sort.
 */
template<typename Iter>
constexpr void merge(Iter first, Iter last) {
    merge(first, last, std::less<>());
}

} // namespace lab::sort
