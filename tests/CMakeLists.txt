project(tests CXX)

set(SRC_LIST
	main.cpp
	tests.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		libsort
)
