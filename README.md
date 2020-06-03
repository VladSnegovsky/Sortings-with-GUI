# Demonstration of sorting algorithms

### Design approach

#### Single responsibility principle

We all know what is single responsibility principle. Sorting algorithm should not notify about changed indexes it should simply sort. C++ has one amazing feature called [ADL](https://en.cppreference.com/w/cpp/language/adl). We used it to write gasket between algorithm and actual container. Sorting algorithm do nothing but swap of indexes. Simple `Value` wrapper behaves like original value and have custom implementation of `swap`. In `swap` we notify (using callback) which iterators of original container were swapped. And here it is: algorithm and container acts like normal and all actual work is hidden in proxy between them. Code for this trick can be found [here](./lib/Utils/Range.hpp). It also supports different kinds of container through compile-time checking of given container properties.

#### GUI

For GUI QML was chosen. It has simple usage and powerful interaction with C++ code. QML has local array. We apply indexes changes reported from C++ step-by-step with animation.

#### Tests

`Catch2` was chosen for tests. It has simple usage and quite powerful features for unit-testing.

### Build & run

To run our application you should met following dependencies:
* Compiler with C++17 support
* `CMake 3.14+`
* `qml-module-qtquick2`
* `qml-module-qtquick-controls2`

Perform following steps to build:
```bash
git clone https://github.com/VladSnegovsky/Sortings-with-GUI
cd Sorting-with-GUI
mkdir build && cd build
cmake ..
make
```

Now in directory `build/bin`directory you have two executables:
* `tests` — tests for sorting algorithms and utilities;
* `gui` — GUI application that demonstrates algorithms;

### Responsibilities
* **Misha Lohachov** — implementation of all sort algorithms and general configuration of project
* **Vlad Snegovsky** — all GUI stuff for project
* **Ostap Mykytiuk** — described above gasket between GUI and algorithm; tying up GUI and actual logic
