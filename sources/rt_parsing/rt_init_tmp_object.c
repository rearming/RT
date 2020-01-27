/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:30 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:19:33 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_tmp(t_tmp *tmp)
{
	tmp->next = NULL;
	tmp->structure_type = 0;
	tmp->type = 0;
	tmp->pos = (cl_float3){{0, 0, 0}};
	tmp->rotation = (cl_float3){{0, 0, 0}};
	tmp->intensity = 0;
	tmp->dir = (cl_float3){{0, 0, 0}};
	tmp->color = (t_color){0};
	tmp->normal =(cl_float3){{0, 0, 0}};
	tmp->radius = 0;
	tmp->angle = 0;
	tmp->len = 0;
	tmp->specularity = 0;
	tmp->texture_number = 0;
	tmp->texture_position = (cl_float3){{0, 0, 0}};
	tmp->checker = 0;
}
