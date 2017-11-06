cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_library(posecartprocess ../PoseCartProcess/PoseCartProcess.cpp)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(test_posecartprocess test_posecartprocess.cpp)
target_link_libraries(test_posecartprocess ${GTEST_LIBRARIES} pthread posecartprocess)
