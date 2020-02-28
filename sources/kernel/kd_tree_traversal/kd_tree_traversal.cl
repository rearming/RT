
bool		ray_aabb_traverse_intersection(t_ray *ray, t_aabb aabb, float *out_near, float *out_far)
{
	float t[10];

	t[1] = (aabb.min.x - ray->origin.x) / ray->dir.x;
	t[2] = (aabb.max.x - ray->origin.x) / ray->dir.x;
	t[3] = (aabb.min.y - ray->origin.y) / ray->dir.y;
	t[4] = (aabb.max.y - ray->origin.y) / ray->dir.y;
	t[5] = (aabb.min.z - ray->origin.z) / ray->dir.z;
	t[6] = (aabb.max.z - ray->origin.z) / ray->dir.z;
	float t_near = fmax(fmax(fmin(t[1], t[2]), fmin(t[3], t[4])), fmin(t[5], t[6]));
	float t_far = fmin(fmin(fmax(t[1], t[2]), fmax(t[3], t[4])), fmax(t[5], t[6]));

	if (t_far < 0 || t_near > t_far)
		return false;
	*out_near = t_near;
	*out_far = t_far;
	return true;
}

void		kd_swap_nodes(
		bool need_swap,
		int left_index,
		int right_index,
		int *out_first,
		int *out_second)
{
	if (need_swap)
	{
		*out_first = right_index;
		*out_second = left_index;
	}
	else
	{
		*out_first = left_index;
		*out_second = right_index;
	}
}

__global const t_kd_arr_tree	*kd_get_node(
		__global const t_kd_arr_tree *arr,
		__global const t_kd_arr_tree *curr_node,
		int side)
{
	if (side == KD_LEFT)
		return (&arr[curr_node->left_index]);
	else
		return (&arr[curr_node->right_index]);
}

# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 2

float	f3_axis(float3 vec, int axis)
{
	if (axis == X_AXIS)
		return vec.s0;
	return axis == Y_AXIS ? vec.s1 : vec.s2;
}

int		kd_tree_traverse(
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *tree_arr,
		__global const int *kd_indices,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit)
{
	int			closest_polygon_index = NOT_SET;
	t_stack		stack;
	float		t_min;
	float		t_max;

	stack.last_elem = 0;
	t_kd_traverse_helper			helper;
	__global const t_kd_arr_tree	*node;

	helper.node_index = 0;

	t_aabb root_aabb = tree_arr[0].aabb;
	if (!(ray_aabb_traverse_intersection(ray, root_aabb, &helper.t_min, &helper.t_max)))
		return (NOT_SET);

	ft_stack_push(&stack, helper);

	float3	inv_ray_dir = native_divide((float3)(1), ray->dir);
	while (stack.last_elem >= 0)
	{
		helper = ft_stack_pop(&stack);
		node = &tree_arr[helper.node_index];
		t_min = helper.t_min;
		t_max = helper.t_max;

		while (node->objects.num == NOT_SET)
		{
			int		axis = node->split_axis;

			float	t_split = ((node->split) - f3_axis(ray->origin, axis)) * f3_axis(inv_ray_dir, axis);

			int		first_node_index;
			int		second_node_index;

			kd_swap_nodes(f3_axis(ray->dir, axis) < 0, node->left_index, node->right_index, &first_node_index, &second_node_index);

			if (t_split >= t_max)
				node = &tree_arr[first_node_index];
			else if (t_split <= t_min)
				node = &tree_arr[second_node_index];
			else
			{
				ft_stack_push(&stack, (t_kd_traverse_helper){second_node_index, t_split, t_max});
				node = &tree_arr[first_node_index];
				t_max = t_split;
			}
		}
		for (int i = 0; i < node->objects.num; ++i)
		{
			int		index = kd_indices[i + node->obj_offset];

			if (ray_triangle_intersect_MT_polygon(
				vertices[polygons[index].vert_i[0]],
				vertices[polygons[index].vert_i[1]],
				vertices[polygons[index].vert_i[2]],
				v_normals[polygons[index].vnorm_i],
				0, 0, 0, /// текстурных вертексов пока нет
				ray, out_best_hit))
			{
				closest_polygon_index = index;
			}
		}
		if (isset(closest_polygon_index))
			return closest_polygon_index;
	}
	return closest_polygon_index;
}
