cmake_minimum_required(VERSION 3.10)
project(nonNewton)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Eigen3 CONFIG REQUIRED)

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
# 方便增加测试用例的函数，只要用addtest(name)即可
enable_testing()
function(addtest testname)
    add_executable(test_${testname} test_${testname}.cpp)
    add_test(NAME test_${testname} COMMAND test_${testname})
    target_include_directories(test_${testname} PRIVATE ${PROJECT_SOURCE_DIR})
    target_link_libraries(test_${testname} PRIVATE Eigen3::Eigen)
endfunction(addtest)

#在这里增加测试
addtest(nonNewton)


# standalone test
add_subdirectory(standalone_tests)