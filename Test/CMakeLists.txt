file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_executable(Test ${srcs} ${hdrs})
target_include_directories(Test PUBLIC ../gtest)
target_link_libraries(Test gtest)
include_directories(../Main)