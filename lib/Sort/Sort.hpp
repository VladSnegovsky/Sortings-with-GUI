#pragma once

#include "Change.hpp"
#include "Type.hpp"

#include <algorithm>
#include <iterator>
#include <variant>
#include <vector>

namespace lab::sort {

template<typename T>
struct Sort
{
    static_assert(sizeof(T) == 0, "No specialization found for your type");
};

template<>
struct Sort<type::Insertion>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<change::Change<It>>
    {
        std::vector<change::Change<It>> changes;

        for (; first != last; ++first) {
            for (auto it = std::next(first); it != last; ++it) {
                if (!comp(*first, *it)) {
                    std::iter_swap(first, it);
                    changes.emplace_back(change::Swap{first, it});
                }
            }
        }

        return changes;
    }
};

template<>
struct Sort<type::Selection>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<change::Change<It>>
    {
        std::vector<change::Change<It>> changes;

        for (; first != last; ++first) {
            const auto min = std::min_element(first, last, comp);
            if (min != first) {
                std::iter_swap(first, min);
                changes.emplace_back(change::Swap{first, min});
            }
        }

        return changes;
    }
};

template<>
struct Sort<type::Bubble>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<change::Change<It>>
    {
        std::vector<change::Change<It>> changes;
        /// TODO
        return changes;
    }
};

template<>
struct Sort<type::Quick>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<change::Change<It>>
    {
        std::vector<change::Change<It>> changes;
        /// TODO
        return changes;
    }
};

template<>
struct Sort<type::Merge>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<change::Change<It>>
    {
        std::vector<change::Change<It>> changes;
        /// TODO
        return changes;
    }
};
    
template<>
struct Sort<type::Heap>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<change::Change<It>>
    {
        std::vector<change::Change<It>> changes;
        /// TODO
        return changes;
    }
};

} // namespace lab::sort
