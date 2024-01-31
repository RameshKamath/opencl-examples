
#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include <utils/cl_helper.hpp>

std::string kernelFunc = std::string("\
__kernel void ProcessMultiDimensionalArray(__global int *data){\
    size_t id = get_global_id(1) * get_global_size(0) + get_global_id(0);\
    data[id] = data[id] * 2;\
}\
");

int main(int argc, char **argv)
{
    std::vector<cl::Platform> platforms;

    cl::Platform::get(&platforms);

    if (platforms.size() <= 0)
    {
        std::cerr << "No Platforms Available!" << std::endl;
        return -1;
    }
    cl::Platform platform = platforms.front();

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    if (devices.size() <= 0)
    {
        std::cerr << "No Devices Available!" << std::endl;
        return -1;
    }
    cl::Device device = devices.front();

    cl::Program::Sources sources(1, std::make_pair(kernelFunc.c_str(), kernelFunc.length() + 1));

    cl::Context context(device);

    cl::Program program(context, sources);

    auto err = program.build("-cl-std=CL1.2");
    if (err != 0)
        std::cerr << "error : " << clGetErrorString(err) << std::endl;

    // int arr[3][2];
    const int numRows = 3;
    const int numCols = 2;
    const int count = numRows * numCols;
    std::array<std::array<int, numCols>, numRows> arr = {{{1, 1}, {2, 2}, {3, 3}}};

    cl::Buffer memBuf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * count, arr.data());

    cl::Kernel kernel(program, "ProcessMultiDimensionalArray", &err);
    if (err != 0)
    {
        std::cerr << "error : " << clGetErrorString(err) << std::endl;
    }

    kernel.setArg(0, memBuf);

    cl::CommandQueue queue(context, device);

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(2, 3));
    queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(int) * count, arr.data());

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            std::cout << arr[i][j] << " " << std::endl;
        }
    }
    std::cin.get();
}