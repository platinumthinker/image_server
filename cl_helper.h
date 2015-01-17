#ifndef CL_HELPER_H
#define CL_HELPER_H

#include <CL/opencl.h>
#include <string>
#include <iostream>
#include <fstream>

/* #define BUILD_FLAGS "-cl-nv-verbose -cl-mad-enable -cl-fast-relaxed-math" */
#define BUILD_FLAGS ""

class CL_Helper
{
    private:
        cl_device_id cdDevice;
        cl_context context;
        cl_command_queue command_queue;
        cl_program program;
        cl_kernel kernel;
    public:
        void init();
        void print_all_platforms();
        void buildProgramFromFile(std::string path);
        int kernel_proc(void *ptr, unsigned int size, unsigned int channels);
};

#endif //CL_HELPER_H
