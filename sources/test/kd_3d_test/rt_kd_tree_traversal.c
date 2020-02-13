#include "rt.h"
#include "rt_kd_tree.h"

bool		ray_aabb_intersection(t_ray ray, t_aabb aabb, float *out_near, float *out_far)
{
	float t[10];

	t[1] = (aabb.bounds.min.x - ray.origin.x) / ray.dir.x;
	t[2] = (aabb.bounds.max.x - ray.origin.x) / ray.dir.x;
	t[3] = (aabb.bounds.min.y - ray.origin.y) / ray.dir.y;
	t[4] = (aabb.bounds.max.y - ray.origin.y) / ray.dir.y;
	t[5] = (aabb.bounds.min.z - ray.origin.z) / ray.dir.z;
	t[6] = (aabb.bounds.max.z - ray.origin.z) / ray.dir.z;
	float t_near = fmaxf(fmaxf(fminf(t[1], t[2]), fminf(t[3], t[4])), fminf(t[5], t[6]));
	float t_far = fminf(fminf(fmaxf(t[1], t[2]), fmaxf(t[3], t[4])), fmaxf(t[5], t[6]));

	if (t_far < 0 || t_near > t_far)
		return false;
	*out_near = t_near;
	*out_far = t_far;
	return true;
}

void		kd_swap_nodes(
		bool need_swap,
		t_kd_tree *left,
		t_kd_tree *right,
		t_kd_tree **out_first,
		t_kd_tree **out_second)
{
	if (need_swap)
	{
		*out_first = right;
		*out_second = left;
	}
	else
	{
		*out_first = left;
		*out_second = right;
	}
}


bool	kd_tree_traverse(t_kd_tree *tree, t_ray ray, int *indices)
{
	t_stack	stack;
	float	t_min;
	float	t_max;

	ft_stack_init(&stack, KD_TREE_MAX_HEIGHT);

	t_kd_traverse_helper	helper;
	t_kd_tree				*node;

	helper.node = tree;
	if (!(ray_aabb_intersection(ray, tree->aabb, &helper.t_min, &helper.t_max)))
	{
//		printf("INTERSECTION WITH ROOT NODE FAILED!\n");
		return (false);
	}

	ft_stack_push(&stack, &helper, sizeof(t_kd_traverse_helper));

	while (stack.last_elem >= 0)
	{
		helper = *((t_kd_traverse_helper*)ft_stack_pop(&stack).data);
		node = helper.node;
		t_min = helper.t_min;
		t_max = helper.t_max;

		while (node->objects.num == NOT_SET)
		{
			int		axis = node->split_axis;
			float	t_split = (node->split - ray.origin.s[axis]) / ray.dir.s[axis];

			t_kd_tree	*first_node;
			t_kd_tree	*second_node;
			kd_swap_nodes(ray.dir.s[axis] < 0, node->left, node->right, &first_node, &second_node);

			if (t_split >= t_max || t_split < 0)
				node = first_node;
			else if (t_split <= t_min)
				node = second_node;
			else
			{
				helper.node = second_node;
				helper.t_min = t_split;
				helper.t_max = t_max;
				ft_stack_push(&stack, &helper, sizeof(t_kd_traverse_helper));
				node = first_node;
				t_max = t_split;
			}
		}
		if (helper.node->objects.num > 0)
		{
//			printf("objects in node:\n");
//			printf("obj num: [%i]\n", helper.node->objects.num);
//			printf("node's split: [%f]\n", helper.node->split);
			for (int i = 0; i < helper.node->objects.num; ++i)
			{
				indices[helper.node->objects.indices[i]] = true;
//				ft_printf("[%i] ", helper.node->objects.indices[i]);
			}
//			ft_printf("\n\n");
//			return (true);
		}
	}
	return false;
}