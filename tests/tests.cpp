#include "catch.hpp"
#include <sortings.hpp>
#include <algorithm>

TEST_CASE("Sorting tests") {
    constexpr auto DefaultSwapper = [](auto& first, auto& second) -> void {std::swap(first, second);};
    constexpr auto DefaultComparator = [](auto first, auto second) -> bool  {return first > second;};
    constexpr auto DefaultChanger = [](auto value) -> void {};
    
    SECTION("Insertion sort") {
        std::vector<int> v = {1, 0, -10, 12, 1002, 20};
        auto vs = v;
        std::sort(vs.begin(), vs.end());
        sorting::insertionSort(v.begin(), v.end(), DefaultSwapper, DefaultComparator, DefaultChanger, DefaultChanger);
        REQUIRE(v == vs);
    }
}
