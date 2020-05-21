#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

namespace detail {
/**
 * @brief Sorts [begin, end) diapason on forward iterators using bubble sort.
 */
 template<typename FIter, typename Comp>
 constexpr void bubble(FIter first, FIter last, Comp comparator, std::forward_iterator_tag) {
     if (first == last) {
         return;
     }

     bool has_changed = true;
     while (has_changed) {
         has_changed = false;
         auto begin = first;
         auto next_iterator = std::next(begin);
         while (next_iterator != last) {
             if (comparator(*next_iterator, *begin)) {
                 std::iter_swap(next_iterator, begin);
                 has_changed = true;
             }
             begin = next_iterator;
             std::advance(next_iterator, 1);
         }
     }
 }

} // namespace detail

 /**
  * @brief Sorts [begin, end) diapason using bubble sort.
  */
 template<typename Iter, typename Comp>
 constexpr void bubble(Iter fisrt, Iter last, Comp comparator) {
     detail::bubble(fisrt, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
 }
 
 /**
  * @brief Sorts [begin, end) diapason using bubble sort.
  */
 template<typename Iter>
 constexpr void bubble(Iter fisrt, Iter last) {
     bubble(fisrt, last, std::less<>());
 }

} // namespace lab::sort
