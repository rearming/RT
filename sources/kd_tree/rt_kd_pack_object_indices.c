/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_pack_object_indices.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rt_pack_kd_object_indices(t_kd_info *kd_info)
{
	cl_int	offset;
	int		i;
	int		j;

	kd_info->indices = rt_safe_malloc(sizeof(cl_int) * kd_info->indices_num);
	offset = 0;
	i = 0;
	while (i < kd_info->nodes_num)
	{
		j = 0;
		while (j < kd_info->tree_arr[i].objects.num)
		{
			kd_info->indices[j + offset] =
					kd_info->tree_arr[i].objects.indices[j];
			j++;
		}
		kd_info->tree_arr[i].obj_offset = offset;
		offset += j;
		i++;
	}
}
