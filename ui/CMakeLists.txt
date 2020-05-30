
find_package(Qt5 COMPONENTS Core Quick)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Add our single resource file
qt5_add_resources(RESOURCES qml.qrc)

set(SRC_LIST main.cpp Sort.cpp)

add_executable(gui ${SRC_LIST} ${RESOURCES})

# Instruct against which modules application should be linked
qt5_use_modules(gui Core Quick)
