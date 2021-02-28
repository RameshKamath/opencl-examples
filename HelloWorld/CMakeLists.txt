cmake_minimum_required(VERSION 3.7)

project(opencl_cpp)

find_package(OpenCL REQUIRED)

message( STATUS current dir :  ${PROJECT_SOURCE_DIR} )
message( STATUS build dir : ${PROJECT_BINARY_DIR})

add_executable(opencl_cpp main.cpp)
target_include_directories(opencl_cpp PUBLIC ${OpenCL_INCLUDE_DIRS})
target_link_libraries(opencl_cpp ${OpenCL_LIBRARIES})