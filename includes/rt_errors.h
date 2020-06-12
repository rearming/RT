#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# define ERR_INV_ARGS1 "invalid number of arguments, "
# define ERR_INV_ARGS2 "expected 1 arg for .json scene file"
# define ERR_INV_ARGS_NUM ERR_INV_ARGS1 ERR_INV_ARGS2
# define ERR_INV_FILE "invalid file!"

# define ERR_MALLOC "malloc() failed!"

# define ERR_SDL_INIT "SDL_Init failed."
# define ERR_SDL_WIN "SDL_Create_Window failed."
# define ERR_SDL_RENDER "SDL_Create_Renderer failed."
# define ERR_SDL_TEXTURE_CREATE "SDL_Create_Texture failed."

# define ERR_READ_KERNEL_FILE "can't open .cl kernel file!"
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
# define ERR_OPENCL_INV_SOURCE_CODE_FILE "error reading opencl source code file"
# define ERR_OPENCL_LOG "clGetProgramBuildLog failed"

# define ERR_OPENCL_RELEASE_PROGRAM "clReleaseProgram failed"
# define ERR_OPENCL_RELEASE_BUFFER "clReleaseBuffer failed"
# define ERR_OPENCL_RELEASE_KERNEL "clReleaseKernel failed"
# define ERR_OPENCL_RELEASE_EVENT "clReleaseEvent failed"

# define ERR_READ_OBJ_FILE "error when reading .obj file"
# define ERR_OBJLOADER_PARSE_OBJ "tinyobjloader failed"

# define ERR_INVALID_JSON_FILE "can't read json scene file"
# define ERR_PARSING_ARRAY "rt_parse error: wrong data in array parameter"
# define ERR_PARSING_WRONG_SCENE_PARAMS "rt_parse error: wrong scene parameters"
# define ERR_PARS_WRONG_PRM "rt_parse error: wrong parameter - "

# define ERR_INVALID_TEXTURE "can't read texture file"
# define ERR_PARSING_WRONG_OBJECT_PARAMS "rt_parse error: wrong params in "
# define ERR_PARSING_WRONG_OBJECT_TYPE "rt_parse error: wrong type of object"
# define ERR_PARSING_WRONG_OBJECT "rt_parse error: wrong object parameter - "

# define ERR_PARSING_SCENE_NOT_FULL "rt_parse error: scene isn't complete"
# define ERR_PARSING_WRONG_LIGHT_PARAMS "rt_parse error: wrong light params"
# define ERR_PARSING_WRONG_CAMERA_PARAMS "rt_parse error: wrong camera params"
# define ERR_PARSING_WRONG_TYPE "rt_parse error: check the type of json_token"
# define ERR_PARSING_MATRIX "rt_parse error: check rotation matrix in object"

# define ERR_PARSING_DUPLICATED_PARAM "rt_parse error: duplicated parameters"
# define ERR_PARSING_DUPLICATED_SKYBOX "skybox image is duplicated"
# define ERR_INVALID_TEXTURE_OBJECT "texture should be only on basic objects"
# define ERR_IVALID_BUMP_INITIALIZATION "wrong initialization of bump_mapping"
#endif
