#include "rt.h"
#include "rt_opencl.h"

t_opencl_mem_obj	rt_check_opencl_memobj(t_opencl_mem_obj mem_obj)
{
	t_opencl_mem_obj	checked_mem_obj;
	cl_char				dummy_ptr;

	if (mem_obj.ptr != NULL || !(mem_obj.mem_flags & CL_MEM_COPY_HOST_PTR))
		// если нам нужно просто создать буфер, то NULL в clCreateBuffer это нормально
		return mem_obj;
	checked_mem_obj.ptr = &dummy_ptr;
	checked_mem_obj.mem_flags = RT_DEFAULT_MEM_FLAG;
	checked_mem_obj.realloc_state = mem_obj.realloc_state; // todo what must be here ?
	checked_mem_obj.renderer_flags = mem_obj.renderer_flags;
	checked_mem_obj.size = sizeof(cl_char);
	return (checked_mem_obj);
}
