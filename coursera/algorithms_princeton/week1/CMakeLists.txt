cmake_minimum_required(VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(QuickFindTest QuickFindTest.cpp)
target_link_libraries(QuickFindTest ${GTEST_LIBRARIES} pthread)
