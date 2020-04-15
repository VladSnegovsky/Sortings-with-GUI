project(tests CXX)

set(CMAKE_CXX_STANDARD 17)

set(SRC_LIST
	main.cpp
	tests.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		libsort
)
