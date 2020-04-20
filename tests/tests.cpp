#include "catch.hpp"

#include <Sort/Insertion.hpp>

#include <array>

TEST_CASE("Sort") {
    using namespace lab;

    SECTION("Insertion") {
        std::array v{1, 0, -10, 12, 1002, 20};
        sort::insertion(v.begin(), v.end());
        REQUIRE(v == std::array{-10, 0, 1, 12, 20, 1002});
    }
}
