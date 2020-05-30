project(GUI)

find_package(Qt5 COMPONENTS Core Quick)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Add our single resource file
qt5_add_resources(RESOURCES qml.qrc)

set(SRC_LIST
    main.cpp
    Sort.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${RESOURCES})

# Instruct against which modules application should be linked
qt5_use_modules(${PROJECT_NAME} Core Quick)

# Link with core library
target_link_libraries(${PROJECT_NAME} libsort)
