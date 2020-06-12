/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_tree_build.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_kd_tree.h"
#include "rt_kd_tree_build.h"

t_kd_tree	*build_kd_tree(t_aabb *all_aabbs, int num_aabbs)
{
	t_kd_tree	*root;
	int			index;

	index = 0;
	root = rt_safe_malloc(sizeof(t_kd_tree));
	root->aabb = get_root_aabb(all_aabbs, num_aabbs);
	root->sah = INFINITY;
	root->objects = get_root_aabb_objects(num_aabbs);
	build_kd_tree_recursive(root, all_aabbs, 0, &index);
	return (root);
}
