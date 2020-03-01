#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# define ERR_INV_ARGS_NUM "invalid number of arguments, expected 1 arg for .json scene file"
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
# define ERR_OPENCL_LOG "clGetProgramBuildLog failed"

# define ERR_READ_OBJ_FILE "error when reading .obj file"
# define ERR_OBJLOADER_PARSE_OBJ "tinyobjloader failed"

# define ERR_INVALID_TEXRTURE_DIR "couldn't open texture ditectory"
# define ERR_INVALID_TEXRTURE "error when reading texture"

# define ERR_INVALID_TEXTURE_DIR 27

# define ERR_PARSING_WRONG_OBJECT_PARAMS "rt_parse error: wrong object params"

# define ERR_PARSING_WRONG_OBJECT "rt_parse error: object is wrong"
# define ERR_PARSING_WRONG_LIGHT_PARAMS "rt_parse error: wrong light params"
# define ERR_PARSING_WRONG_CAMERA_PARAMS "rt_parse error: wrong camera params"
# define ERR_PARSING_CAMERA "rt_parse error: camera is not initialized correctly"
# define ERR_PARSING_WRONG_PARAM "rt_parse error: wrong params"
# define ERR_PARSING_WRONG_COLOR "rt_parse error: wrong color/diffuse/specular param"
# define ERR_PARSING_WRONG_TYPE "rt_parse error: check the type, it's not object/light/camera"
# define ERR_PARSING_WRONG_FORMAT "rt_parse error: wrong type of parameter"
# define ERR_PARSING_DUPLICATED_PARAM "rt_parse error: duplicated parameters"
# define ERR_PARSING_WRONG_CL_PARAM "rt_parse error: wrong cl parameters"
# define ERR_PRSING_DUPLICATED_SKYBOX "rt_parse error: skybox image is duplicated "

# define ERR_INVALID_JSON_FILE "can't read json scene file"

#endif
