cmake_minimum_required(VERSION 3.0)
project(gui_sorting CXX)

set(CMAKE_CXX_STANDARD 17)

set(TOP_DIR ${CMAKE_SOURCE_DIR})
set(TESTS_DIR ${TOP_DIR}/tests)
set(UI_DIR ${TOP_DIR}/ui)
set(LIB_DIR ${TOP_DIR}/lib)

# output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include libraries
add_subdirectory(${LIB_DIR})

# include tests
add_subdirectory(${TESTS_DIR})

# include ui
add_subdirectory(${UI_DIR})
