#include "rt.h"

/*
**	TODO do parsing gfoote
*/

t_scene		rt_parse_scene(const char *json_scene_file)
{
	t_scene		scene;
	RT_UNUSED(json_scene_file);
	scene = get_hardcoded_scene();
	return (scene);
	RT_UNUSED(rt_correct_scene(&scene));
}
