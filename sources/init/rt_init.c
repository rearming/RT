#include "rt.h"
#include "rt_opencl.h"
#include "rt_parsing.h"

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
	out_rt->scene = rt_parse_scene(json_scene_file);
	if (g_textures.texture_info_size > 0)
		rt_textures_init();
	out_rt->renderer_flags = RENDER_DEFAULT;
	//printf("camera pos: [%0.3f] [%0.3f] [%0.3f]\n",out_rt->scene.camera.pos.x, out_rt->scene.camera.pos.y, out_rt->scene.camera.pos.z);
	//printf("camera rotation: [%0.3f] [%0.3f] [%0.3f]\n",out_rt->scene.camera.rotation.x, out_rt->scene.camera.rotation.y, out_rt->scene.camera.rotation.z);
	rt_load_obj_files(&out_rt->scene.meshes);
#ifndef DEBUG_LOADING
	rt_init_events(&out_rt->events);
#endif

}
