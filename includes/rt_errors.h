#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# define ERR_INV_ARGS_NUM "invalid number of arguments!"
# define ERR_INV_FILE "invalid file!"

# define ERR_MALLOC "malloc() failed!"

# define ERR_SDL_INIT "SDL_Init failed."
# define ERR_SDL_WIN "SDL_Create_Window failed."
# define ERR_SDL_RENDER "SDL_Create_Renderer failed."
# define ERR_SDL_TEXTURE_CREATE "SDL_Create_Texture failed."

# define ERR_USAGE 12
# define ERR_OPENCL "something went wrong in OpenCL!"
# define ERR_OPENCL_CLEAN "error when cleaning OpenCL objects"
# define ERR_OPENCL_SETARG "clSetKernelArg failed"
# define ERR_OPENCL_GET_PLATFORM_ID "clGetPlatformIDs failed!"
# define ERR_OPENCL_GET_DEVICE_ID "clGetDeviceIDs failed!"
# define ERR_OPENCL_CREATE_CONTEXT "clCreateContext failed!"
# define ERR_OPENCL_CREATE_QUEUE "clCreateCommandQueue failed"
# define ERR_OPENCL_CREATE_PROGRAM "clCreateProgramWithSource failed"
# define ERR_OPENCL_BUILD_PROGRAM "clBuildProgram failed"
# define ERR_OPENCL_CREATE_KERNEL "clCreateKernel failed"
# define ERR_OPENCL_CREATE_BUFFER "clCreateBuffer failed"
# define ERR_OPENCL_RUN_KERNELS "clEnqueueNDRangeKernel failed"
# define ERR_OPENCL_READ_BUFFER "clEnqueueReadBuffer failed"
# define ERR_OPENCL_INV_SOURCE_CODE_FILE "error when reading opencl source code file"

# define ERR_READFILE_OBJ "error when reading .obj file"
# define ERR_OBJLOADER_PARSE_OBJ "tinyobjloader failed"

#endif
