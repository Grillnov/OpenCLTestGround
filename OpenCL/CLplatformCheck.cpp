#include <CL\cl.h>
#include <iostream>

static const char* ErrorInfo(cl_int error)
{
	static const char* strings[] =
	{
		// Error Codes
		"CL_SUCCESS"                                  //   0
		, "CL_DEVICE_NOT_FOUND"                         //  -1
		, "CL_DEVICE_NOT_AVAILABLE"                     //  -2
		, "CL_COMPILER_NOT_AVAILABLE"                   //  -3
		, "CL_MEM_OBJECT_ALLOCATION_FAILURE"            //  -4
		, "CL_OUT_OF_RESOURCES"                         //  -5
		, "CL_OUT_OF_HOST_MEMORY"                       //  -6
		, "CL_PROFILING_INFO_NOT_AVAILABLE"             //  -7
		, "CL_MEM_COPY_OVERLAP"                         //  -8
		, "CL_IMAGE_FORMAT_MISMATCH"                    //  -9
		, "CL_IMAGE_FORMAT_NOT_SUPPORTED"               //  -10
		, "CL_BUILD_PROGRAM_FAILURE"                    //  -11
		, "CL_MAP_FAILURE"                              //  -12

		, ""    //  -13
		, ""    //  -14
		, ""    //  -15
		, ""    //  -16
		, ""    //  -17
		, ""    //  -18
		, ""    //  -19

		, ""    //  -20
		, ""    //  -21
		, ""    //  -22
		, ""    //  -23
		, ""    //  -24
		, ""    //  -25
		, ""    //  -26
		, ""    //  -27
		, ""    //  -28
		, ""    //  -29

		, "CL_INVALID_VALUE"                            //  -30
		, "CL_INVALID_DEVICE_TYPE"                      //  -31
		, "CL_INVALID_PLATFORM"                         //  -32
		, "CL_INVALID_DEVICE"                           //  -33
		, "CL_INVALID_CONTEXT"                          //  -34
		, "CL_INVALID_QUEUE_PROPERTIES"                 //  -35
		, "CL_INVALID_COMMAND_QUEUE"                    //  -36
		, "CL_INVALID_HOST_PTR"                         //  -37
		, "CL_INVALID_MEM_OBJECT"                       //  -38
		, "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"          //  -39
		, "CL_INVALID_IMAGE_SIZE"                       //  -40
		, "CL_INVALID_SAMPLER"                          //  -41
		, "CL_INVALID_BINARY"                           //  -42
		, "CL_INVALID_BUILD_OPTIONS"                    //  -43
		, "CL_INVALID_PROGRAM"                          //  -44
		, "CL_INVALID_PROGRAM_EXECUTABLE"               //  -45
		, "CL_INVALID_KERNEL_NAME"                      //  -46
		, "CL_INVALID_KERNEL_DEFINITION"                //  -47
		, "CL_INVALID_KERNEL"                           //  -48
		, "CL_INVALID_ARG_INDEX"                        //  -49
		, "CL_INVALID_ARG_VALUE"                        //  -50
		, "CL_INVALID_ARG_SIZE"                         //  -51
		, "CL_INVALID_KERNEL_ARGS"                      //  -52
		, "CL_INVALID_WORK_DIMENSION"                   //  -53
		, "CL_INVALID_WORK_GROUP_SIZE"                  //  -54
		, "CL_INVALID_WORK_ITEM_SIZE"                   //  -55
		, "CL_INVALID_GLOBAL_OFFSET"                    //  -56
		, "CL_INVALID_EVENT_WAIT_LIST"                  //  -57
		, "CL_INVALID_EVENT"                            //  -58
		, "CL_INVALID_OPERATION"                        //  -59
		, "CL_INVALID_GL_OBJECT"                        //  -60
		, "CL_INVALID_BUFFER_SIZE"                      //  -61
		, "CL_INVALID_MIP_LEVEL"                        //  -62
		, "CL_INVALID_GLOBAL_WORK_SIZE"                 //  -63
		, "CL_UNKNOWN_ERROR_CODE"
	};

	if (error >= -63 && error <= 0)
		return strings[-error];
	else
		return strings[64];
}

static const char* deviceTypeInfo(cl_device_type deviceType)
{
	if (deviceType == CL_DEVICE_TYPE_GPU)
		return "GPU";
	else if (deviceType == CL_DEVICE_TYPE_CPU)
		return "CPU";
	else if (deviceType == CL_DEVICE_TYPE_ACCELERATOR)
		return "Accelerator";
	else
		return "Unknown type";
}

void CLplatformCheck()
{
	cl_uint numofPlatforms = 0;
	cl_int status = 0;
	status = clGetPlatformIDs(0, nullptr, &numofPlatforms);
	if (status != 0)
	{
		std::cout << "Error occured when acquiring OpenCL platform information." << std::endl;
		std::cout << ErrorInfo(status) << std::endl;
		return;
	}
	std::cout << "Platform check complete. " << numofPlatforms << " platforms were found." << std::endl << std::endl;
	cl_platform_id *platforms = new cl_platform_id[numofPlatforms];
	status = clGetPlatformIDs(numofPlatforms, platforms, nullptr);

	for (unsigned i = 0; i != numofPlatforms; ++i)
	{
		size_t strSize = 0;

		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, nullptr, &strSize);
		if (status != 0)
		{
			std::cout << "Error occured attempting to acquire platform information." << std::endl;
			std::cout << ErrorInfo(status) << std::endl;
			return;
		}
		char* Name = new char[strSize];
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, strSize, Name, nullptr);

		std::cout << "Platform " << i << "'s name: " << Name << std::endl;
		delete[] Name;

		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 0, nullptr, &strSize);
		Name = new char[strSize];
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, strSize, Name, nullptr);

		std::cout << "Platform " << i << " is provided by vendor: " << Name << std::endl;
		delete[] Name;

		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 0, nullptr, &strSize);
		Name = new char[strSize];
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, strSize, Name, nullptr);

		std::cout << "Platform " << i << "'s support info: " << Name << std::endl;
		delete[] Name;

		cl_uint numDevices = 0;
		status = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
		if (status != 0)
		{
			std::cout << "Error occured attempting to query platform " << i << "'s devices" << std::endl;
			std::cout << ErrorInfo(status) << std::endl;
			return;
		}
		
		cl_device_id *devices = new cl_device_id[numDevices];
		status = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevices, devices, nullptr);
		std::cout << "Devices found on platform " << i << " are as follow." << std::endl;
		for (unsigned j = 0; j != numDevices; ++j)
		{
			cl_device_type deviceType;
			status = clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(cl_device_type), &deviceType, nullptr);
			std::cout << "Device " << j << " found on platform " << i << " is a " << deviceTypeInfo(deviceType) << " device." << std::endl;
			
			char *vendorName = nullptr;
			status = clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 0, nullptr, &strSize);
			vendorName = new char[strSize];
			status = clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, strSize, vendorName, nullptr);
			std::cout << "Device " << j << " is provided by vendor: " << vendorName << std::endl;
			delete[] vendorName;
		}
		delete[] devices;
		std::cout << std::endl;
	}
	delete[] platforms;
}

int main()
{
	CLplatformCheck();
}