#include <iostream>
#include <fstream>
#include <string>

#include <utils/cl_helper.hpp>

int main(int argc, char **argv)
{
    std::string kernelFunc = "__kernel void HelloWorld(__global char *data) { data[0] = 'H'; data[1] = 'e'; data[2] = 'l'; data[3] = 'l'; data[4] = 'o'; data[5] = ' '; data[6] = 'w'; data[7] = 'o'; data[8] = 'r'; data[9] = 'l'; data[10] = 'd'; data[11] = '!'; data[12] = '\\0';}";

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

    try
    {
        cl_int err = program.build("-cl-std=CL1.2");
        if (err != 0)
        {
            std::cerr << "error : " << clGetErrorString(err) << std::endl;
        }
        char buf[16];

        cl::Buffer memBuf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY, sizeof(buf));

        cl::Kernel kernel(program, "HelloWorld", &err);
        if (err != 0)
        {
            std::cerr << "error : " << clGetErrorString(err) << std::endl;
        }

        kernel.setArg(0, memBuf);

        cl::CommandQueue queue(context, device);
        queue.enqueueTask(kernel);
        queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buf), buf);

        std::cout << buf << std::endl;
        std::cin.get();
    }
    catch (std::exception &err)
    {
        std::cerr << "error : " << err.what() << std::endl;
    }
}