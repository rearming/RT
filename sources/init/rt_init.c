#include "rt.h"
#include "rt_opencl.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"
#include "rt_events.h"
#include "rt_load_textures.h"
#include "rt_load_obj_files.h"

void		rt_bzero_data(t_rt *rt)
{
	bzero_g_textures();
	bzero_kd_info(&rt->kd_info);
	bzero_meshes(&rt->scene.meshes);
}

void		rt_init(t_rt *out_rt, const char *json_scene_file)
{
	rt_sdl_init();
	rt_opencl_init();
	rt_bzero_data(out_rt);
	out_rt->render_actions = ACTION_ALL;
	out_rt->render_state = STATE_NOTHING;
	out_rt->scene = rt_parse_scene(json_scene_file, &out_rt->render_options);
	rt_init_render_params(&out_rt->params, out_rt->scene.clInfo);//todo fix this "clInfo" thing [gfoote]
	if (g_textures.texture_info_size > 0)
		rt_textures_init();
	else
		out_rt->render_state |= STATE_NO_TEXTURES;
	if (g_textures.skybox_info->skybox_exist)
		rt_skybox_init();
	else
		out_rt->render_state |= STATE_NO_SKYBOX;
	if (rt_load_obj_file(out_rt->scene.obj_file, &out_rt->scene.meshes))
	{
		if (!rt_kd_tree_import(&out_rt->kd_info, out_rt->scene.obj_file))
		{
			rt_get_kd_object(&out_rt->scene.meshes, &out_rt->kd_info);
			rt_kd_tree_export(&out_rt->kd_info, out_rt->scene.obj_file);
		}
	}
	else
		out_rt->render_state |= STATE_NO_MESH;
//	if (!rt_bit_isset(out_rt->render_state, STATE_NO_MESH))
//		rt_kd_tree_export(&out_rt->kd_info);
	out_rt->events = EVENT_NOTHING;
}
