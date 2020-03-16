#include "rt.h"
#include "rt_opencl.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"

void		rt_init(t_rt *out_rt, const char *json_scene_file)
{
	rt_sdl_init();
	rt_opencl_init();
	out_rt->render_state = STATE_ALL;
	out_rt->scene = rt_parse_scene(json_scene_file, &out_rt->render_options);
	rt_init_render_params(&out_rt->params, out_rt->scene.clInfo);//todo fix this gfoote
	if (g_textures.texture_info_size > 0)
		rt_textures_init();
	if (g_textures.skybox_info->skybox_exist == true)
		rt_skybox_init();
	rt_load_obj_file(out_rt->scene.obj_file, &out_rt->scene.meshes);
	out_rt->kd_info = rt_get_kd_object(&out_rt->scene.meshes);
	out_rt->events = EVENT_NOTHING;
}
