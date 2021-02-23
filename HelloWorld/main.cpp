
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <iostream>
#include <CL/cl.hpp>
#include <fstream>
#include <string>

#include "cl_error.h"

int main(int argc, char **argv)
{
    if(argc <2){
        std::cout << "Usage: need HelloWorld.cl path."<< std::endl;
        return 1;
    }

    std::string path = argv[1];

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

    for (cl::Device device : devices)
    {
        std::string vendor = device.getInfo<CL_DEVICE_VENDOR>();
        std::string version = device.getInfo<CL_DEVICE_VERSION>();

        std::cout << "vendor: " << vendor << ", version: " << version << std::endl;
    }

    cl::Device device = devices.front();

    std::ifstream helloWorldFile(path);
    if(helloWorldFile.is_open()){

    std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>()));

    cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

    cl::Context context(device);

    cl::Program program(context, sources);

    auto err = program.build("-cl-std=CL1.2");
    if (err != 0)
        std::cerr << "error : " << clGetErrorString(err) << std::endl;

    char buf[16];

    cl::Buffer memBuf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY, sizeof(buf));

    cl::Kernel kernel(program, "HelloWorld", &err);
    if(err != 0)
        std::cerr << "error : " << clGetErrorString(err) << std::endl;

    kernel.setArg(0, memBuf);

    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buf), buf);


    std::cout << buf <<std::endl;
    std::cin.get();
    }
    else{
        std::cout << "error : " << "Couldn't open opencl file" << std::endl;
    }
}