cmake_minimum_required(VERSION 3.10)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(service_locator)

# UnitTests
add_executable( service_locator_tests 
                    src/ServiceLocator.cpp
                    test/ServiceLocatorTests.cpp)

target_link_libraries(service_locator_tests PUBLIC gtest gtest_main gmock pthread)
target_include_directories(service_locator_tests PUBLIC inc test/mocks)

# Example
add_executable( example
                    src/ServiceLocator.cpp
                    example/main.cpp)

target_include_directories(example PUBLIC inc example)