#include "catch.hpp"

#include <Sort/Insertion.hpp>
#include <Utils/Range.hpp>

#include <algorithm>
#include <array>
#include <list>

TEST_CASE("[lab][sort]") {
    using namespace lab;

    SECTION("Insertion") {
        std::array arr{1, 0, -10, 12, 1002, 20};
        sort::insertion(arr.begin(), arr.end());
        REQUIRE(arr == std::array{-10, 0, 1, 12, 20, 1002});
    }
}

TEST_CASE("[lab][utils][range]") {
    using namespace lab;

    SECTION("Creation") {
        SECTION("Array") {
            auto array = std::array{3, 2, 1};
            utils::Range range{array};
        }

        SECTION("Vector") {
            auto vector = std::vector{3, 2, 1};
            utils::Range range{vector};
        }

        SECTION("List") {
            auto list = std::list{{3, 2, 1}};
            utils::Range range{list};
        }
    }

    SECTION("Access") {
        auto array = std::array{3, 2, 1};
        utils::Range range{array};
        sort::insertion(range.begin(), range.end());
        REQUIRE(array == std::array{1, 2, 3});
    }
}
