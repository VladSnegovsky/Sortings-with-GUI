#pragma once

#include <functional>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace lab::sort {

namespace detail {

/**
 * @brief Applies hepify method to heap
 */
template<typename Iter, typename Comp>
constexpr void _heapify(Iter first, Iter last, const Comp comparator) {
    if (first == last) {
        return;
    }
    
    size_t begin_pos = 1;
    auto begin = std::next(first);
    while (begin != last) {
        size_t father_pos = (begin_pos - 1) / 2;
        auto father = std::next(first, father_pos);

        auto begin_saved = begin;
        size_t begin_pos_saved = begin_pos;
        while ((begin_pos != 0) && (comparator(*father, *begin))) {
            std::iter_swap(father, begin);
            begin_pos = father_pos;
            begin = father;
            if (father_pos != 0) {
                father_pos = (father_pos - 1) / 2;
            }
            father = std::next(first, father_pos);
        }
        begin = begin_saved;
        begin_pos = begin_pos_saved;
        std::advance(begin, 1);
        ++begin_pos;
    }
}

/**
 * @brief Restores heap after removing an element
 */
template<typename Iter, typename Comp>
constexpr void _restore_heap(Iter first, Iter last, Comp comparator) {
    if (first == last) {
        return;
    }

    size_t size = std::distance(first, last);
    size_t current_pos = 0;
    size_t child_pos = 1;
    auto current = first;
    auto child = std::next(first);
    bool move_next = false;

    do {
        move_next = false;
        auto selected_child = child;
        size_t selected_pos = child_pos;
        if (child_pos < size) {
            if (child_pos + 1 < size) {
                if (comparator(*child, *std::next(child))) {
                    selected_child = std::next(child);
                    selected_pos = child_pos + 1;
                } else {
                    selected_child = child;
                    selected_pos = child_pos;
                }
            }
        } else {
            break;
        }
        if (comparator(*current, *selected_child)) {
            move_next = true;
            std::iter_swap(current, selected_child);
            current = selected_child;
            current_pos = selected_pos;
            child_pos = 2 * child_pos + 1;
            if (child_pos < size) {
                child = std::next(first, child_pos);
            }
        }
    } while (move_next);
}

/**
 * @brief Sorts [begin, end) diapason on forward iterators using heap sort.
 */
template<typename FIter, typename Comp>
constexpr void heap(FIter first, FIter last, Comp comparator, std::forward_iterator_tag) {
     detail::_heapify(first, last, comparator);
     int size = std::distance(first, last);
     --size;
    while (size > 0) {
         auto to_swap = std::next(first, size);
         std::iter_swap(to_swap, first);
         detail::_restore_heap(first, std::next(first, size), comparator);
         --size;
    }
}

} // namespace detail

/**
 * @brief Sorts [begin, end) diapason using heap sort.
 */
template<typename Iter, typename Comp>
constexpr void heap(Iter first, Iter last, Comp comparator) {
    detail::heap(first, last, comparator, typename std::iterator_traits<Iter>::iterator_category());
}

/**
 * @brief Sorts [begin, end) diapason using heap sort.
 */
template<typename Iter>
constexpr void heap(Iter first, Iter last) {
    heap(first, last, std::less<>());
}

} // namespace lab::sort
