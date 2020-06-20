/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck_norminette.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 14:38:13 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/20 17:00:22 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"

void		fuck_norminette2(u_int32_t options, SDL_Rect rect)
{
	rect.y = IMP_Y;
	rect.x = SECOND_COL_X;
	g_gui.obj[imp_btn] = (t_transform){ .rect = rect, .bit = RENDER_IMPRESSIVE,
			.state = options & RENDER_IMPRESSIVE, .text = IMPRESSIVE_LABEL,
			.action = imp_btn, .callback = button_callback, .type = IMP_BTN,
			.color = get_color_from_hex((options & RENDER_IMPRESSIVE)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = SMOOTH_Y;
	g_gui.obj[smooth_btn] = (t_transform){ .rect = rect,
			.bit = RENDER_SMOOTH_NORMALS, .type = SMOOTH_BTN,
			.state = options & RENDER_SMOOTH_NORMALS, .text = SMOOTH_LABEL,
			.action = smooth_btn, .callback = button_callback,
			.color = get_color_from_hex((options & RENDER_SMOOTH_NORMALS)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
}

void		fuck_norminette1(u_int32_t options, SDL_Rect rect)
{
	rect.y = ANTI_AL_Y;
	g_gui.obj[aa_btn] = (t_transform){ .rect = rect,
			.bit = RENDER_ANTI_ALIASING,
			.state = options & RENDER_ANTI_ALIASING, .text = ANTI_AL_LABEL,
			.action = aa_btn, .callback = button_callback, .type = ANTI_AL_BTN,
			.color = get_color_from_hex((options & RENDER_ANTI_ALIASING)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = SKYBOX_Y;
	g_gui.obj[sb_btn] = (t_transform){ .rect = rect, .bit = RENDER_SKYBOX,
			.state = options & RENDER_SKYBOX, .text = SKYBOX_LABEL,
			.action = sb_btn, .callback = button_callback, .type = SKYBOX_BTN,
			.color = get_color_from_hex((options & RENDER_SKYBOX)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = BACKFACE_C_Y;
	fuck_norminette2(options, rect);
}

void		init_render_options_button(u_int32_t options)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){.x = FIRST_COL_X, .y = MSH_Y,
			.h = BTN_BIG_SIZE, .w = HALF_GUI};
	g_gui.obj[msh_btn] = (t_transform){ .rect = rect, .bit = RENDER_MESH,
			.state = options & RENDER_MESH, .text = MESHES_LABEL,
			.action = msh_btn, .callback = button_callback, .type = MESHES_BTN,
			.color = get_color_from_hex((options & RENDER_MESH)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = OBJ_Y;
	g_gui.obj[obj_btn] = (t_transform){ .rect = rect,
			.state = options & RENDER_OBJECTS, .text = OBJECTS_LABEL,
			.bit = RENDER_OBJECTS,
			.action = obj_btn, .callback = button_callback, .type = OBJECTS_BTN,
			.color = get_color_from_hex((options & RENDER_OBJECTS)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = TEXTURE_Y;
	g_gui.obj[texture_btn] = (t_transform){ .rect = rect,
			.bit = RENDER_TEXTURES, .state = options & RENDER_TEXTURES,
			.callback = button_callback,
			.action = texture_btn, .text = TEXTURE_LABEL, .type = TEXTURES_BTN,
			.color = get_color_from_hex((options & RENDER_TEXTURES)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	fuck_norminette1(options, rect);
}

void		init_render_states_button(u_int32_t states)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){.x = SECOND_COL_X, .y = DOF_Y,
			.h = BTN_BIG_SIZE, .w = HALF_GUI};
	g_gui.obj[blur_btn] = (t_transform){ .rect = rect, .text = BLUR_LABEL,
			.state = states & STATE_POSTPROCESS_DOF,
			.bit = STATE_POSTPROCESS_DOF,
			.action = blur_btn, .callback = button_callback, .type = BLUR_BTN,
			.color = get_color_from_hex((states & STATE_POSTPROCESS_DOF)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = SEPIA_Y;
	g_gui.obj[sepia_btn] = (t_transform){ .rect = rect, .text = SEPIA_LABEL,
			.state = states & STATE_POSTPROCESS_SEPIA,
			.bit = STATE_POSTPROCESS_SEPIA,
			.action = sepia_btn, .callback = button_callback, .type = SEPIA_BTN,
			.color = get_color_from_hex((states & STATE_POSTPROCESS_SEPIA)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = TUNES_Y;
	g_gui.obj[tunes_btn] = (t_transform){ .rect = rect, .text = CARTOON_LABEL,
			.state = states & STATE_POSTPROCESS_CARTOON, .action = tunes_btn,
			.callback = button_callback, .bit = STATE_POSTPROCESS_CARTOON,
			.type = CARTOON_BTN, .color = get_color_from_hex((states &
			STATE_POSTPROCESS_CARTOON) ? (BTN_COLOR_CLICK)
			: (BTN_COLOR_NONACTIVE))};
}
