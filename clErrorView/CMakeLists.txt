cmake_minimum_required(VERSION 3.7)

project(opencl_clErrorView LANGUAGES CXX VERSION 0.0.1)
message( STATUS "Start :  ${PROJECT_NAME}" )
message( STATUS "    current dir :  ${PROJECT_SOURCE_DIR}" )
message( STATUS "    build dir : ${PROJECT_BINARY_DIR}")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
message( STATUS "Done :  ${PROJECT_NAME}" )

