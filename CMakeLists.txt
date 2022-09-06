cmake_minimum_required(VERSION 3.7)
 
project(opencl-example LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(clErrorView)
add_subdirectory(HelloWorld)
add_subdirectory(ExternalKernel)
add_subdirectory(HardwareInfo)
add_subdirectory(MultiDimProc)