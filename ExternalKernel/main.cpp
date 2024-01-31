#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include <utils/cl_helper.hpp>

int main(int argc, char **argv)
{
    std::string kernelPath;
    std::string kernelFunc;
    if (argc > 1)
    {
        kernelPath = argv[1];
        kernelFunc = argv[2];
    }
    else
    {
        std::cout << "Trying with default Kernelfile and Fucnction" << std::endl;
        std::string parent_path = std::filesystem::weakly_canonical(std::filesystem::path(argv[0])).parent_path();
        kernelPath = parent_path + "/externalKernel.cl";
        kernelFunc = "HelloWorld";
    }
    std::cout << "Using kernel in path: " << kernelPath << std::endl;
    std::cout << "with function name: " << kernelFunc << std::endl;

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

    std::ifstream kernelFilename(kernelPath);
    if (kernelFilename.is_open())
    {

        std::string src(std::istreambuf_iterator<char>(kernelFilename), (std::istreambuf_iterator<char>()));

        cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

        cl::Context context(device);

        cl::Program program(context, sources);

        auto err = program.build("-cl-std=CL1.2");
        if (err != 0)
        {
            std::cerr << "error : " << clGetErrorString(err) << std::endl;
        }

        char buf[16];

        cl::Buffer memBuf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY, sizeof(buf));

        cl::Kernel kernel(program, kernelFunc.c_str(), &err);
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
    else
    {
        std::cerr << "error : "
                  << "Couldn't open or find opencl file" << std::endl;
        std::clog << "Usage: <bin_location>/opencl_ExternalKernel <kernel_location>.cl <kernel_function_name>" << std::endl;
    }
}