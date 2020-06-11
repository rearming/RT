#include "rt.h"
#include "rt_kd_tree.h"

bool				kd_is_obj_in_aabb(t_aabb root_aabb, t_aabb obj_aabb)
{
	if ((obj_aabb.min.x <= root_aabb.max.x
		&& obj_aabb.min.y <= root_aabb.max.y
		&& obj_aabb.min.z <= root_aabb.max.z
		&& obj_aabb.max.x >= root_aabb.min.x
		&& obj_aabb.max.y >= root_aabb.min.y
		&& obj_aabb.max.z >= root_aabb.min.z)
		||
		(obj_aabb.max.x >= root_aabb.min.x
		&& obj_aabb.max.y >= root_aabb.min.y
		&& obj_aabb.max.z >= root_aabb.min.z
		&& obj_aabb.min.x <= root_aabb.max.x
		&& obj_aabb.min.y <= root_aabb.max.y
		&& obj_aabb.min.z <= root_aabb.max.z))
		return (true);
	return (false);
}

t_aabb_objects		kd_get_objects_in_aabb(
		t_aabb aabb,
		t_aabb *all_aabbs,
		t_aabb_objects *prev_objects)
{
	t_aabb_objects	aabb_objects;
	int				i;

	aabb_objects.num = 0;
	aabb_objects.indices = rt_safe_malloc(sizeof(int) * prev_objects->num);
	i = 0;
	while (i < prev_objects->num)
	{
		if (kd_is_obj_in_aabb(aabb, all_aabbs[prev_objects->indices[i]]))
		{
			aabb_objects.indices[aabb_objects.num] = prev_objects->indices[i];
			aabb_objects.num++;
		}
		i++;
	}
	return (aabb_objects);
}

float				kd_get_aabb_area(t_aabb aabb)
{
	return ((aabb.max.x - aabb.min.x)
			* (aabb.max.y - aabb.min.y)
			* (aabb.max.z - aabb.min.z));
}

t_aabb_objects		get_root_aabb_objects(int num_aabbs)
{
	t_aabb_objects	aabb_objects;
	int				i;

	i = 0;
	aabb_objects.num = num_aabbs;
	aabb_objects.indices = rt_safe_malloc(sizeof(int) * num_aabbs);
	while (i < num_aabbs)
	{
		aabb_objects.indices[i] = i;
		i++;
	}
	return (aabb_objects);
}
