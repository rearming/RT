#include "rt.h"
#include "rt_opencl.h"

t_opencl_mem_obj	rt_check_opencl_memobj(t_opencl_mem_obj mem_obj)
{
	t_opencl_mem_obj	checked_mem_obj;
	cl_char				dummy_ptr;

	if (mem_obj.ptr || !(mem_obj.mem_flags & CL_MEM_COPY_HOST_PTR))
		return (mem_obj);
	checked_mem_obj.ptr = &dummy_ptr;
	checked_mem_obj.mem_flags = RT_DEFAULT_MEM_FLAG;
	checked_mem_obj.render_action = mem_obj.render_action;
	checked_mem_obj.size = sizeof(cl_char);
	return (checked_mem_obj);
}

void				rt_opencl_prepare_memory(t_rt *rt, uint32_t render_action)
{
	t_opencl_mem_obj	opencl_mem_objs[20];

	rt_opencl_prepare_mem_arr1(rt, opencl_mem_objs);
	rt_opencl_prepare_mem_arr2(rt, opencl_mem_objs);
	rt_opencl_prepare_mem_arr3(rt, opencl_mem_objs);
	rt_opencl_prepare_mem_arr4(rt, opencl_mem_objs);
	rt_opencl_prepare_mem_arr5(rt, opencl_mem_objs);
	g_opencl.buffers_num = sizeof(opencl_mem_objs) / sizeof(t_opencl_mem_obj);
	rt_opencl_alloc_buffers(render_action, opencl_mem_objs);
}
