project(libsort CXX)

set(SRC_LIST
    Sort/bubble.hpp
    Sort/heap.hpp
    Sort/insertion.hpp
    Sort/merge.hpp
    Sort/quick.hpp
    Sort/selection.hpp

    Utils/Range.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${SRC_LIST})

target_include_directories (${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:libsort>
)
