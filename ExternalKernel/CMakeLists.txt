cmake_minimum_required(VERSION 3.7)

project(opencl_ExternalKernel)

message( STATUS " Project : ${PROJECT_NAME} " )
message( STATUS "    source dir : ${PROJECT_SOURCE_DIR}" )
message( STATUS "    build dir : ${PROJECT_BINARY_DIR}")

add_executable(${PROJECT_NAME} main.cpp)
add_dependencies(${PROJECT_NAME} opencl_utils)
target_link_libraries(${PROJECT_NAME} PUBLIC opencl_utils)

message( STATUS "    copy externalKernel to build dir")
file(COPY ${PROJECT_SOURCE_DIR}/externalKernel.cl DESTINATION ${PROJECT_BINARY_DIR}/)
message( STATUS " Done :  ${PROJECT_NAME}  " )
