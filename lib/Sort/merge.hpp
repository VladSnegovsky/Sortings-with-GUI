#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <forward_list>

namespace lab::sort {

namespace detail {
    
/**
 * @brief Sorts [begin, end) diapason on random access iterators using merge sort.
 */
template<typename RAIter, typename Comp>
constexpr void merge(RAIter first, RAIter last, Comp comparator, const std::random_access_iterator_tag tag) {
    if (const auto distance = std::distance(first, last); distance > 1) {
        const auto middle = std::next(first, distance / 2);
        merge(first, middle, comparator, tag);
        merge(middle, last, comparator, tag);
        std::inplace_merge(first, middle, last, comparator);
    }
}

/**
 * @brief Sorts [begin, end) diapason on forward iterators using merge sort.
 */
template<typename FIter, typename Comp>
constexpr void merge(FIter first, FIter last, Comp comparator, const std::forward_iterator_tag tag) {
    if (first == last || std::next(first) == last) {
        return;
    }

    std::forward_list<typename std::iterator_traits<FIter>::value_type> container;
    const auto middle = std::next(first, std::distance(first, last) / 2);

    std::move(first, middle, std::front_inserter(container));
    merge(container.begin(), container.end(), comparator, tag);
    merge(middle, last, comparator, tag);

    std::merge(
        std::make_move_iterator(container.begin()), 
        std::make_move_iterator(container.end()),
        std::make_move_iterator(middle), 
        std::make_move_iterator(last), 
        first, 
        comparator
    );
}

} // namespace detail

/**
 * @brief Sorts [begin, end) diapason using merge sort.
 */
template<typename Iter, typename Comp>
constexpr void merge(Iter first, Iter last, Comp comparator) {
    detail::merge(first, last, comparator, typename std::iterator_traits<Iter>::iterator_category{});
}

/**
 * @brief Sorts [begin, end) diapason using merge sort.
 */
template<typename Iter>
constexpr void merge(Iter first, Iter last) {
    merge(first, last, std::less<>{});
}

} // namespace lab::sort
