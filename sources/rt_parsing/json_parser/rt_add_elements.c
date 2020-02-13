/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:44 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:19:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_array(cl_float3 *elem, json_t *value)
{
	json_t	*tmp;
	int		i;

	i = -1;
	if (json_array_size(value) == 3)
	{
		while (++i < 3)
		{
			tmp = json_array_get(value, i);
			if (!json_is_number(tmp))
				printf("error");
			else
				elem->s[i] = json_is_integer(tmp) ? json_integer_value(tmp)
					: json_real_value(tmp);
		}
	}
}

void 	add_elements_in_array(t_tmp	*tmp, int type_of_element, int array_type, json_t *value)
{
	if (array_type == 1)
	{
		if (type_of_element == POS)
			add_array(&tmp->pos, value);
		else if (type_of_element == ROTATION)
			add_array(&tmp->rotation, value);
		else if (type_of_element == DIRECTION)
			add_array(&tmp->dir, value);
		else if (type_of_element == COLOR)
			add_array(&tmp->color, value);
		else if (type_of_element == NORMAL)
			add_array(&tmp->normal, value);
		else
			add_array(&tmp->texture_position, value);
	}
	else
	{
		if (type_of_element == AMBIENCE)
			add_array(&tmp->ambient, value);
		else if (type_of_element ==DIFFUSE)
			add_array(&tmp->diffuse, value);
		else if (type_of_element == SPECULAR)
			add_array(&tmp->specular, value);
		else
			add_array(&tmp->emission_color, value);
	}
}