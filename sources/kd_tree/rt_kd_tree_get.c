/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_tree_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_kd_tree.h"

void		bzero_kd_info(t_kd_info *out_kd_info)
{
	out_kd_info->tree_arr = NULL;
	out_kd_info->indices = NULL;
	out_kd_info->indices_num = 0;
	out_kd_info->nodes_num = 0;
}

void		rt_get_kd_object(t_meshes *meshes, t_kd_info *out_kd_info)
{
	t_aabb			*all_aabbs;
	t_kd_tree		*kd_tree;
	t_kd_arr_tree	*kd_arr_tree;

	out_kd_info->indices_num = 0;
	out_kd_info->nodes_num = 0;
	all_aabbs = rt_get_all_aabbs(meshes);
	kd_tree = build_kd_tree(all_aabbs, meshes->num_polygons);
	kd_arr_tree = kd_tree_to_array(
			kd_tree, &out_kd_info->nodes_num, &out_kd_info->indices_num);
	free(all_aabbs);
	free_kd_tree(kd_tree, false);
	out_kd_info->tree_arr = kd_arr_tree;
	rt_pack_kd_object_indices(out_kd_info);
}
