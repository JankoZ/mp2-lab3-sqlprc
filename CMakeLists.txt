cmake_minimum_required(VERSION 3.1)
project(Lab3)

add_subdirectory(Main)

option(TESTS "Build tests?" OFF)
if(TESTS)
	add_subdirectory(gtest)
	add_subdirectory(Test)
endif()