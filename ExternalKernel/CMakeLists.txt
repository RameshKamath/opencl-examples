cmake_minimum_required(VERSION 3.7)

project(opencl_ExternalKernel)

find_package(OpenCL REQUIRED)

message( STATUS current dir :  ${PROJECT_SOURCE_DIR} )
message( STATUS build dir : ${PROJECT_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARIES})