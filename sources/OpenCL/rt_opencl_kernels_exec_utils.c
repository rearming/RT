#include "rt.h"
#include "rt_opencl.h"
#include "rt_opencl_params_defines.h"

void	set_render_kernel_args(t_render_kernel *render_kernel)
{
	const int	args_num = 18;
	int			err;

	rt_set_kernel_args(render_kernel->kernel, args_num,
		RT_CL_MEM_SCENE, RT_CL_MEM_OBJECTS, RT_CL_MEM_LIGHTS, RT_CL_MEM_PARAMS,
		RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE, RT_CL_MEM_KD_INDICES,
		RT_CL_MEM_MESHES_INFO, RT_CL_MEM_POLYGONS, RT_CL_MEM_VERTICES,
		RT_CL_MEM_V_NORMALS, RT_CL_MEM_V_TEXTURES,
		RT_CL_MEM_TEXTURE_INFO, RT_CL_MEM_TEXTURE_LIST,
		RT_CL_MEM_SKYBOX_INFO, RT_CL_MEM_SKYBOX_LIST,
		RT_CL_MEM_IMG_DATA,
		RT_CL_MEM_DEPTH_BUFFER);
	err = clSetKernelArg(render_kernel->kernel, args_num,
			sizeof(cl_mem), &render_kernel->img_data_float);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

int		switch_img_buffers(int *in_buffer, int *out_buffer)
{
	static int		in_img_buffer = RT_CL_MEM_IMG_DATA;
	static int		out_img_buffer = RT_CL_MEM_OUT_IMG_DATA;
	int				read_return;

	read_return = NOT_SET;
	if (in_buffer && out_buffer)
	{
		*in_buffer = in_img_buffer;
		*out_buffer = out_img_buffer;
		ft_swap(&in_img_buffer, &out_img_buffer);
	}
	else
	{
		read_return = in_img_buffer;
		in_img_buffer = RT_CL_MEM_IMG_DATA;
		out_img_buffer = RT_CL_MEM_OUT_IMG_DATA;
	}
	return (read_return);
}
