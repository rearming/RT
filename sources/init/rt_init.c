#include <time.h>
#include "rt.h"
#include "rt_opencl.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"
#include "rt_events.h"
#include "rt_load_textures.h"
#include "rt_load_obj_files.h"
#include "rt_init.h"

void		rt_bzero_data(t_rt *rt)
{
	bzero_g_textures();
	bzero_kd_info(&rt->kd_info);
	bzero_meshes(&rt->scene.meshes);
}

static void	rt_init_textures(t_rt *out_rt)
{
	if (g_textures.texture_info_size > 0 &&
		(out_rt->render_options & RENDER_TEXTURES))
		rt_textures_init();
	else
		out_rt->render_state |= STATE_NO_TEXTURES;
	if (g_textures.skybox_info->skybox_exist &&
		(out_rt->render_options & RENDER_SKYBOX))
		rt_skybox_init();
	else
		out_rt->render_state |= STATE_NO_SKYBOX;
}

void 		rt_init(t_rt *out_rt, const char *json_scene_file, uint32_t init_options)
{
	rt_sdl_init();
	rt_opencl_init();
	rt_bzero_data(out_rt);
	out_rt->render_actions = ACTION_ALL;
	out_rt->render_state = STATE_NOTHING;
	out_rt->scene = rt_parse_scene(json_scene_file, &out_rt->render_options);
	rt_init_render_params(&out_rt->params, out_rt->scene.clInfo);//todo fix this "clInfo" thing [gfoote]
	rt_init_textures(out_rt);
	if (rt_load_obj_file(out_rt->scene.obj_file, &out_rt->scene.meshes))
	{
		if (!rt_kd_tree_import(&out_rt->kd_info, out_rt->scene.obj_file)
		|| rt_bit_isset(init_options, INIT_KD_REGENERATE))
		{
			clock_t	start = clock();
			rt_get_kd_object(&out_rt->scene.meshes, &out_rt->kd_info);
			printf("kd-tree built in [%f] sec\n",
					(double)(clock() - start) / CLOCKS_PER_SEC);
			rt_kd_tree_export(&out_rt->kd_info, out_rt->scene.obj_file);
		}
		rt_print_kd_tree_info(&out_rt->kd_info);
	}
	else
		out_rt->render_state |= STATE_NO_MESH;
	out_rt->events = EVENT_NOTHING;
}
