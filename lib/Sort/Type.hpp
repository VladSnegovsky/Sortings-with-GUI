#pragma once

#include <variant>

namespace lab::sort::type {

struct Insertion {};
struct Selection {};
struct Bubble {};
struct Quick {};
struct Merge {};
struct Heap {};

using Type = std::variant<
    Insertion,
    Selection,
    Bubble,
    Quick,
    Merge,
    Heap
>;

} // namespace lab::sort::type
