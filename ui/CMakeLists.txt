project(ui)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.12.5/gcc_64/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Designer REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SRC_LIST
	main.cpp
)

set(QT5_LIST
    Qt5::Widgets
    Qt5::Core
    Qt5::Designer
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		libsort
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${QT5_LIST}
)

target_include_directories(libsort
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)
