cmake_minimum_required(VERSION 3.14)
project(uc1677c_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.4.12
)
FetchContent_MakeAvailable(doctest)

add_executable(tests
    main.cpp
    uc1677c_tests.cc
    cgs164a00_tests.cc
    cgs214a06_tests.cc
)

target_compile_options(tests PRIVATE -Wall -Wextra)
target_include_directories(tests PRIVATE ../include)
target_link_libraries(tests PRIVATE doctest::doctest)

enable_testing()
add_test(NAME all COMMAND tests)