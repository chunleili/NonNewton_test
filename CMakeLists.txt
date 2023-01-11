cmake_minimum_required(VERSION 3.10)
project(nonNewton)


find_package(Eigen3 CONFIG REQUIRED)

# 方便增加测试用例的函数，只要用addtest(name)即可
enable_testing()
function(addtest testname)
    add_executable(test_${testname} test_${testname}.cpp)
    add_test(NAME test_${testname} COMMAND test_${testname})
    target_include_directories(test_${testname} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(test_${testname} PRIVATE Eigen3::Eigen)
endfunction(addtest)

#在这里增加测试
addtest(nonNewton)

set_target_properties(test_nonNewton PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin
)