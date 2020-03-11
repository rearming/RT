#include "rt.h"
#include "rt_opencl.h"

void rt_wavefront_setup_buffers(t_rt *rt, t_renderer_params render_params)
{
	const int	memobj_num = 37;

	rt_wavefront_alloc_buffers(rt, memobj_num,
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.camera, sizeof(t_camera), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //todo лучей может быть больше пикселей в случае с АА
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // pixel_indices

			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene, sizeof(t_scene), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.objects, sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.lights, sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info, sizeof(t_kd_info), RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.tree_arr, sizeof(t_kd_arr_tree) * rt->kd_info.nodes_num, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.indices, sizeof(cl_int) * rt->kd_info.indices_num, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.meshes_info, sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.polygons, sizeof(t_polygon) * rt->scene.meshes.num_polygons, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.vertices, sizeof(cl_float3) * rt->scene.meshes.num_vertices, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_normals, sizeof(cl_float3) * rt->scene.meshes.num_v_normals, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //material rays buffer
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // material hit obj indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // material hit polygon indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // material hit pixel indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_rayhit) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // material ray hit buffer
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // counter

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // texture hit buffers
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_rayhit) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //counter

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // skybox hit buffers
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //counter
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // img_data (int буфер пикселей)

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //out rays buffer (for shade kernels)
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //out rays pixel indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // out rays buffer len

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // временный float3 буфер цветов (на один сэмпл pathtrace)
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // постоянный float3 буфер цветов
			rt_check_opencl_memobj((t_opencl_mem_obj){&render_params, sizeof(t_renderer_params), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_float) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), // raytrace light intensity buffer

			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_info, sizeof(t_texture_info) * g_textures.texture_info_size, RT_DEFAULT_MEM_FLAG, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_list, sizeof(t_texture_info) * g_textures.texture_list_size, RT_DEFAULT_MEM_FLAG, false, RENDER_ALWAYS})
	);
}

void		rt_wavefront_bzero_buffer(cl_mem mem, size_t size)
{
	cl_char		pattern[1];

	pattern[0] = 0;
	clEnqueueFillBuffer(g_opencl.queue, mem, pattern, sizeof(cl_char), size, 0, 0, NULL, NULL);
}

void		rt_wavefront_alloc_buffers(t_rt *rt, int memobj_num, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;

	va_start(ap, memobj_num);
	mem_obj_i = 0;
	if (g_opencl.shared_buffers_copy_done == false) //маллочить память ТОЛЬКО ОДИН РАЗ БЛЯТБ
		g_opencl.wavefront_shared_buffers = rt_safe_malloc(memobj_num * sizeof(t_cl_buffer));
	while (mem_obj_i < memobj_num)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (memobj.copy == true || g_opencl.shared_buffers_copy_done == false)
		{
			g_opencl.wavefront_shared_buffers[mem_obj_i].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			if (!memobj.ptr)
				rt_wavefront_bzero_buffer(g_opencl.wavefront_shared_buffers[mem_obj_i].mem, memobj.size);
			g_opencl.wavefront_shared_buffers[mem_obj_i].copy_mem = memobj.copy;
			g_opencl.wavefront_shared_buffers[mem_obj_i].renderer_flags = memobj.renderer_flags;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		mem_obj_i++;
	}
	g_opencl.shared_buffers_copy_done = true;
	va_end(ap);
}
