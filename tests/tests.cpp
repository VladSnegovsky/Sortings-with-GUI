#include "catch.hpp"

#include <Sort/bubble.hpp>
#include <Sort/heap.hpp>
#include <Sort/insertion.hpp>
#include <Sort/merge.hpp>
#include <Sort/quick.hpp>
#include <Sort/selection.hpp>

#include <Utils/Range.hpp>

#include <algorithm>
#include <array>
#include <list>
#include <forward_list>

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

TEST_CASE("Sorting tests") {
    using namespace lab::sort;

    const std::vector<std::vector<int>> RAIter_cases = {
        {},
        {42},
        {1, 0, -10, 12, 1002, 20},
        {1, 0, -10, 12, 1002, 0, 20},
        {1, 1, 2, 3, 3, 3, 10},
        {10, 9, 8, 8, 1, 1, -1},
    };
    auto RAIter_direct_expected = RAIter_cases;
    auto RAIter_reverse_expected = RAIter_cases;
    
    for (size_t test_id = 0; test_id < RAIter_cases.size(); ++test_id) {
        std::sort(RAIter_direct_expected[test_id].begin(), RAIter_direct_expected[test_id].end());
        std::sort(RAIter_reverse_expected[test_id].begin(), RAIter_reverse_expected[test_id].end(), std::greater<int>());
    }
    
    const std::vector<std::forward_list<int>> FIter_cases = {
        {},
        {42},
        {1, 0, -10, 12, 1002, 20},
        {1, 0, -10, 12, 1002, 0, 20},
        {1, 1, 2, 3, 3, 3, 10},
        {10, 9, 8, 8, 1, 1, -1},
    };
    auto FIter_direct_expected = FIter_cases;
    auto FIter_reverse_expected = FIter_cases;
    for (size_t test_id = 0; test_id < FIter_cases.size(); ++test_id) {
        FIter_direct_expected[test_id].sort();
        FIter_reverse_expected[test_id].sort(std::greater<int>());
    }
    
    const std::vector<std::list<int>> BIter_cases = {
        {},
        {42},
        {1, 0, -10, 12, 1002, 20},
        {1, 0, -10, 12, 1002, 0, 20},
        {1, 1, 2, 3, 3, 3, 10},
        {10, 9, 8, 8, 1, 1, -1},
    };
    auto BIter_direct_expected = BIter_cases;
    auto BIter_reverse_expected = BIter_cases;
    for (size_t test_id = 0; test_id < BIter_cases.size(); ++test_id) {
        BIter_direct_expected[test_id].sort();
        BIter_reverse_expected[test_id].sort(std::greater<int>());
    }
    
    SECTION("Bubble sort") {
        SECTION("Random access iterators") {
            SECTION("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    bubble(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    bubble(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Bidirectional iterators") {
            SECTION("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    bubble(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    bubble(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Forward iterators") {
            SECTION("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    bubble(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    bubble(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SECTION("Quick sort") {
        SECTION("Random access iterators") {
            SECTION("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    quick(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    quick(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Bidirectional iterators") {
            SECTION("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    quick(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    quick(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Forward iterators") {
            SECTION("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    quick(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    quick(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SECTION("Insertion sort") {
        SECTION("Random access iterators") {
            SECTION("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    insertion(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    insertion(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Bidirectional iterators") {
            SECTION("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    insertion(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    insertion(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Forward iterators") {
            SECTION("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    insertion(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    insertion(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SECTION("Merge sort") {
        SECTION("Random access iterators") {
            SECTION("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    merge(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    merge(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Bidirectional iterators") {
            SECTION("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    merge(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    merge(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Forward iterators") {
            SECTION("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    merge(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    merge(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SECTION("Selection sort") {
        SECTION("Random access iterators") {
            SECTION("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    selection(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    selection(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Bidirectional iterators") {
            SECTION("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    selection(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    selection(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Forward iterators") {
            SECTION("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    selection(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    selection(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    }
    SECTION("Heap sort") {
        SECTION("Random access iterators") {
            SECTION("Direct order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    heap(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == RAIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = RAIter_cases;
                for (size_t case_id = 0; case_id < RAIter_cases.size(); ++case_id) {
                    heap(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == RAIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Bidirectional iterators") {
            SECTION("Direct order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    heap(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == BIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = BIter_cases;
                for (size_t case_id = 0; case_id < BIter_cases.size(); ++case_id) {
                    heap(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == BIter_reverse_expected[case_id]);
                }
            }
        }
        SECTION("Forward iterators") {
            SECTION("Direct order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    heap(results[case_id].begin(), results[case_id].end());
                    REQUIRE(results[case_id] == FIter_direct_expected[case_id]);
                }
            }
            SECTION("Reverse order") {
                auto results = FIter_cases;
                for (size_t case_id = 0; case_id < FIter_cases.size(); ++case_id) {
                    heap(results[case_id].begin(), results[case_id].end(), std::greater<int>());
                    REQUIRE(results[case_id] == FIter_reverse_expected[case_id]);
                }
            }
        }
    } 
}
