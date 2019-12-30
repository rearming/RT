#include "rt.h"

/*
**	TODO do parsing gfoote
*/

t_scene		rt_parse_scene(const char *json_scene_file)
{
	RT_UNUSED(json_scene_file);
	return (get_hardcoded_scene());
}
