
#include <iostream>
#include <string>
#include <vector>

#include <utils/cl_helper.hpp>

int main(int argc, char **argv)
{
    std::vector<cl::Platform> platforms;

    cl::Platform::get(&platforms);

    if (platforms.size() <= 0)
    {
        std::cerr << "No Platforms Available!" << std::endl;
        return -1;
    }

    std::cout << "Number of Platform Available: " << platforms.size() << std::endl;

    std::string platformVendor;
    for (cl::Platform platform : platforms)
    {
        platform.getInfo((cl_platform_info)CL_PLATFORM_VENDOR, &platformVendor);
        std::cout << "Platform is by: " << platformVendor << std::endl;

        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        std::cout << " Devices Available: " << devices.size() << std::endl;

        if (devices.size() <= 0)
        {
            std::cerr << " No Devices Available!" << std::endl;
            return -1;
        }

        int i = 1;
        for (cl::Device device : devices)
        {
            std::string vendor = device.getInfo<CL_DEVICE_VENDOR>();
            std::string version = device.getInfo<CL_DEVICE_VERSION>();

            std::cout << " Device No: " << i << " vendor: " << vendor << ", version: " << version << std::endl;
            i++;
        }
    }

    std::cin.get();
}