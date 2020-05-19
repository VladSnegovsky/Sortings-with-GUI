#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

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

 /**
  * @brief Sorts [begin, end) diapason using bubble sort.
  */
 template<typename Iter, typename Comp = std::less<typename std::iterator_traits<Iter>::value_type>>
 constexpr void bubble(Iter fisrt, Iter last, Comp comparator = Comp()) {
     bubble(fisrt, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
 }

} // namespace lab::sort
