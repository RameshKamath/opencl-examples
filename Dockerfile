FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive 

RUN apt update && apt-get install -y build-essential cmake gdb

# to get the platform or devices
# run clinfo in terminal to make sure platform and device is available
RUN apt install -y opencl-headers ocl-icd-opencl-dev ocl-icd-libopencl1 beignet-opencl-icd beignet-dev pocl-opencl-icd clinfo

CMD ["clinfo"]