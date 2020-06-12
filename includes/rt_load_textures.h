/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_load_textures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LOAD_TEXTURES_H
# define RT_LOAD_TEXTURES_H

void	bzero_g_textures(void);

void	rt_init_render_params(t_render_params *out_opencl_params,
		t_cl_info cl_info);
int		init_basic_textures_parameters(void);
void	rt_add_start_position(int i);
char	*found_file(const char *file, char **folders_names);

#endif
