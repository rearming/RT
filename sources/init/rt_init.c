#include "rt.h"
#include "rt_opencl.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"

void		rt_init_events(t_events *events)
{
	events->w = false;
	events->a = false;
	events->s = false;
	events->d = false;
	events->info = false;
	events->space = false;
	events->lshift = false;
}

void		rt_init(t_rt *out_rt, const char *json_scene_file)
{
#ifndef DEBUG_LOADING
	rt_sdl_init();
	rt_opencl_init();
#endif
	out_rt->renderer_flags = 0;
	out_rt->scene = rt_parse_scene(json_scene_file, &out_rt->renderer_flags);
	if (g_textures.texture_info_size > 0)
		rt_textures_init();
	if (g_textures.skybox_info->skybox_exist == true)
		rt_skybox_init();
	rt_load_obj_file(NULL, &out_rt->scene.meshes);
	out_rt->kd_info = rt_get_kd_object(&out_rt->scene.meshes);
#ifndef DEBUG_LOADING
	rt_init_events(&out_rt->events);
#endif

}
