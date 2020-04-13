/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_boolean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:07:17 by gfoote            #+#    #+#             */
/*   Updated: 2020/03/10 17:07:18 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_boolean(t_tmp *tmp, const char *key, json_t *value,
					  uint32_t *renderer_flags)
{
	if (tmp->structure_type != RENDER_PARAMS)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_PARAM, key));
	else
	{
		if (ft_strequ(key, "render objects"))
			*renderer_flags = json_is_true(value) ? *renderer_flags
				| RENDER_OBJECTS : *renderer_flags & ~RENDER_OBJECTS;
		else if (ft_strequ(key, "render anti aliasing"))
			*renderer_flags = json_is_true(value) ? *renderer_flags
			| RENDER_ANTI_ALIASING : *renderer_flags & ~RENDER_ANTI_ALIASING;
		else if (ft_strequ(key, "backface culling"))
			*renderer_flags = json_is_true(value) ? *renderer_flags |
			RENDER_BACKFACE_CULLING : *renderer_flags &
			~RENDER_BACKFACE_CULLING;
		else if (ft_strequ(key, "enabled"))
		{
			if (tmp->type == MESH)
				*renderer_flags = json_is_true(value) ? *renderer_flags
					| RENDER_MESH : *renderer_flags & ~RENDER_MESH;
			else if (tmp->type == TEXTURES || tmp->type == SKYBOX)
				*renderer_flags = json_is_true(value) ? *renderer_flags
					| RENDER_TEXTURES : *renderer_flags & ~RENDER_TEXTURES;
		}
	}
}
