/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_structs.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct				s_ray
{
	float3					origin;
	float3					dir;
	float3					energy;
}							t_ray;

typedef struct				s_rayhit
{
	float3					pos;
	float					distance;
	float3					normal;
}							t_rayhit;

typedef struct				s_kd_traverse_helper
{
	int						node_index;
	float					t_min;
	float					t_max;
}							t_kd_traverse_helper;

typedef struct				s_stack
{
	t_kd_traverse_helper	helpers[KD_TREE_MAX_HEIGHT];
	int						last_elem;
}							t_stack;

