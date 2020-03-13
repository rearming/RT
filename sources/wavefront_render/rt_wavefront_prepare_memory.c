#include "rt.h"
#include "rt_opencl.h"
#include "rt_wavefront_render.h"

#define MAX_AA_BUFFER_SIZE (WIN_WIDTH * WIN_HEIGHT * 2)

void wavefront_setup_buffers(t_rt *rt,
							 t_renderer_params render_params,
							 uint32_t render_state,
							 uint32_t max_work_size)
{
	g_opencl.wf_shared_buffers_len = 40;

	printf("setting up gpu buffers\n");
	rt_wavefront_alloc_buffers(render_state,
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.camera, sizeof(t_camera), RT_DEFAULT_MEM_FLAG, STATE_CAMERA_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // максимально возможное для AA
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // pixel_indices

			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene, sizeof(t_scene), RT_DEFAULT_MEM_FLAG, STATE_LIGHTS_CHANGED | STATE_OBJECTS_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.objects, sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, STATE_OBJECTS_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.lights, sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, STATE_LIGHTS_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info, sizeof(t_kd_info), RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.tree_arr, sizeof(t_kd_arr_tree) * rt->kd_info.nodes_num, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.indices, sizeof(cl_int) * rt->kd_info.indices_num, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.meshes_info, sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.polygons, sizeof(t_polygon) * rt->scene.meshes.num_polygons, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.vertices, sizeof(cl_float3) * rt->scene.meshes.num_vertices, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_normals, sizeof(cl_float3) * rt->scene.meshes.num_v_normals, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_textures, sizeof(cl_float3) * rt->scene.meshes.num_v_textures, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED, RENDER_ALWAYS}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // material hit obj indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // material hit polygon indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // material hit pixel indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_rayhit) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // material ray hit buffer
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // material rays counter

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // texture hit obj indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // texture hit polygon indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // texture hit pixel indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_rayhit) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // texture ray hit buffer
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // texture rays counter

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // skybox hit obj indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), //skybox rays buffer
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // skybox rays counter

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // img_data (int буфер пикселей)
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), //out rays buffer (for shade kernels)
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), //out rays pixel indices
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // out rays buffer len

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // временный float3 буфер цветов (на один сэмпл pathtrace)
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}), // постоянный float3 буфер цветов
			rt_check_opencl_memobj((t_opencl_mem_obj){&render_params, sizeof(t_renderer_params), RT_DEFAULT_MEM_FLAG, STATE_PARAMS_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_float) * max_work_size, CL_MEM_READ_WRITE, STATE_NO_AA_INIT | STATE_AA_RAYS_GENERATED, RENDER_ALWAYS}), // raytrace light intensity buffer

			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_info, sizeof(t_texture_info) * g_textures.texture_info_size, RT_DEFAULT_MEM_FLAG, STATE_TEXTURES_CHANGED, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_list, sizeof(t_texture_info) * g_textures.texture_list_size, RT_DEFAULT_MEM_FLAG, STATE_TEXTURES_CHANGED, RENDER_ALWAYS}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * MAX_AA_BUFFER_SIZE, CL_MEM_READ_WRITE, STATE_CAMERA_CHANGED, RENDER_ALWAYS}), // rays buffer for anti-aliasing
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * MAX_AA_BUFFER_SIZE, CL_MEM_READ_WRITE, STATE_CAMERA_CHANGED, RENDER_ALWAYS}), // pixel indices buffer for anti-aliasing
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_uint), CL_MEM_READ_WRITE, STATE_EXIT, RENDER_ALWAYS}) // anti-aliasing rays buffer len
	);
}

void		rt_wavefront_bzero_buffer(cl_mem mem, size_t size)
{
	cl_char		pattern[1];

	pattern[0] = 0;
	clEnqueueFillBuffer(g_opencl.queue, mem, pattern, sizeof(cl_char), size, 0, 0, NULL, NULL);
}

void		rt_wavefront_alloc_buffers(uint32_t render_state, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;
	static bool			first_copy = true;

	va_start(ap, render_state);
	mem_obj_i = 0;
	if (first_copy)
		g_opencl.wf_shared_buffers = rt_safe_malloc(g_opencl.wf_shared_buffers_len * sizeof(t_cl_buffer));
	while (mem_obj_i < g_opencl.wf_shared_buffers_len)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (memobj.realloc_state & render_state)
		{
			g_opencl.wf_shared_buffers[mem_obj_i].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			if (!memobj.ptr)
				rt_wavefront_bzero_buffer(g_opencl.wf_shared_buffers[mem_obj_i].mem, memobj.size);
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		else if (first_copy)
			g_opencl.wf_shared_buffers[mem_obj_i].mem = NULL;
		g_opencl.wf_shared_buffers[mem_obj_i].realloc_state = memobj.realloc_state;
		g_opencl.wf_shared_buffers[mem_obj_i].renderer_flags = memobj.renderer_flags;
		mem_obj_i++;
	}
	first_copy = false;
	va_end(ap);
}
