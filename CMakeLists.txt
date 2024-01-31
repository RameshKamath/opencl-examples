cmake_minimum_required(VERSION 3.7)
 
project(opencl_examples LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)


add_library(opencl_utils INTERFACE)
target_include_directories(opencl_utils INTERFACE ${PROJECT_SOURCE_DIR})

find_package(OpenCL REQUIRED)
add_compile_definitions(CL_HPP_TARGET_OPENCL_VERSION=220)
message(STATUS "OpenCL found: ${OPENCL_FOUND}")
message(STATUS "OpenCL includes: ${OpenCL_INCLUDE_DIRS}")
message(STATUS "OpenCL CXX includes: ${OpenCL_HAS_CPP_BINDINGS}")
message(STATUS "OpenCL libraries: ${OpenCL_LIBRARIES}")
add_dependencies(opencl_utils OpenCL::OpenCL)
target_link_libraries(opencl_utils INTERFACE OpenCL::OpenCL)

message( STATUS "Build Examples" )
add_subdirectory(HelloWorld)
add_subdirectory(ExternalKernel)
add_subdirectory(HardwareInfo)
add_subdirectory(MultiDimProc)
