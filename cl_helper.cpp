#include "cl_helper.h"
#include <cstring>

void CL_Helper::init()
{
	cl_platform_id platform_id[100];
	cl_device_id device_id[100];
	cl_int error;
    cl_uint ret_num_platform, ret_num_devices;

	error = clGetPlatformIDs(100, platform_id, &ret_num_platform);
    if (error != CL_SUCCESS)
    {
        printf("error %d\n", CL_OUT_OF_HOST_MEMORY);
        exit(1);
    }

    // Get devece ID for GPU device type
	error = clGetDeviceIDs(platform_id[0], CL_DEVICE_TYPE_GPU, 1,
            device_id, &ret_num_devices);
    if (error != CL_SUCCESS)
    {
        printf("error %d\n", error);
        exit(2);
    }

	// Create OpenCL context
	context = clCreateContext(0, 1, device_id, NULL, NULL, &error);
    if (error != CL_SUCCESS)
    {
        printf("error %d\n", error);
        exit(3);
    }

	command_queue = clCreateCommandQueue(context, device_id[0], 0, &error);
    if (error != CL_SUCCESS)
    {
        printf("error %d\n", error);
        exit(4);
    }
}

void CL_Helper::print_all_platforms()
{
	cl_platform_id platform_id[100];
	cl_uint error, ret_num_platform;

	error = clGetPlatformIDs(100, platform_id, &ret_num_platform);
    if (error != CL_SUCCESS)
    {
        printf("error %d\n", CL_OUT_OF_HOST_MEMORY);
        exit(1);
    }
    printf("=== %d OpenCL platform(s) found: ===\n", ret_num_platform);
	for (unsigned int i=0; i < ret_num_platform; i++)
	{
		char buffer[10240];
		printf("  -- %d --\n", i);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_PROFILE, 10240, buffer, NULL);
		printf("  PROFILE = %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_VERSION, 10240, buffer, NULL);
		printf("  VERSION = %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_NAME, 10240, buffer, NULL);
		printf("  NAME = %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_VENDOR, 10240, buffer, NULL);
		printf("  VENDOR = %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_EXTENSIONS, 10240, buffer, NULL);
		printf("  EXTENSIONS = %s\n", buffer);
	}
}

void CL_Helper::buildProgramFromFile(std::string source_path)
{
    cl_int err;
    // Buffer to hold source for compilation
    std::ifstream file(source_path);
    std::string str, source;
    while (std::getline(file, str))
    {
        source += str;
        source.push_back('\n');
    }
    /* char source_char[8192];//as 1 char space for null is also required */
    /* strcpy(source_char, source.c_str()); */
    size_t ss = source.size();
    const char *si = source.c_str();

    // Create OpenCL program with source code
    cl_program program = clCreateProgramWithSource(context, 1,
            (const char **)&si, (const size_t *)&ss, &err);

    // Build the program (OpenCL JIT compilation)
    std::cerr << "Calling clBuildProgram..." << std::endl;
    err = clBuildProgram(program, 0, NULL, BUILD_FLAGS, NULL, NULL);
    std::cerr << "OK" << std::endl;

    cl_build_status build_status;
    err = clGetProgramBuildInfo(program, cdDevice,
    CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &build_status, NULL);

    char *build_log;
    size_t ret_val_size;
    err = clGetProgramBuildInfo(program, cdDevice, CL_PROGRAM_BUILD_LOG, 0,
            NULL, &ret_val_size);
    build_log = new char[ret_val_size + 1];
    err = clGetProgramBuildInfo(program, cdDevice, CL_PROGRAM_BUILD_LOG,
            ret_val_size, build_log, NULL);

    build_log[ret_val_size] = '\0';
    std::cerr << build_log << std::endl;

	kernel = clCreateKernel(program, "desaturate", &err);
    if (err != CL_SUCCESS)
    {
        printf("error %d\n", err);
        exit(7);
    }
}

int CL_Helper::kernel_proc(void *ptr, unsigned int size, unsigned int channels)
{
    cl_int error, ret;
    const size_t globalSize = size / channels, localSize = 1;

    cl_mem mem = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &ret);
    if (ret != CL_SUCCESS)
        return 1;
    cl_mem out = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &ret);
    if (ret != CL_SUCCESS)
        return 2;

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &out);

    ret = clEnqueueWriteBuffer(command_queue, mem, CL_TRUE, 0, size, ptr,
            0, NULL, NULL);
    if (ret != CL_SUCCESS)
    {
        printf("error71 %d\n", ret);
        return 10;
    }

	error = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &globalSize,
            &localSize, 0, NULL, NULL);
    if (error != CL_SUCCESS)
    {
        printf("error4 %d\n", error);
        return 1;
    }

	error = clEnqueueReadBuffer(command_queue, out, CL_TRUE, 0,
			size, ptr, 0, NULL, NULL);
    if (error != CL_SUCCESS)
    {
        printf("error5 %d\n", error);
        return 1;
    }
	clFinish(command_queue);

    clReleaseMemObject(mem);
    clReleaseMemObject(out);
    return 0;
}
