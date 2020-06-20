/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"
#include "rt_colors.h"
#include "rt_window_params.h"

void		create_title(void)
{
	SDL_Rect	rect;
	t_transform	title;

	rect = (SDL_Rect){.x = 0, .y = 0, .h = GUI_TITLE, .w = WIN_GUI_WIDTH};
	title = (t_transform){ .rect = rect,
			.state = label, .text = RT_GUI_TITLE,
			.color = get_color_from_hex(WHITE)};
	render_button_with_params(title, g_gui.title, 0);
}

void		init_object_panel(void)
{
	SDL_Rect rect;

	rect = (SDL_Rect){.x = PANEL_BORDER, .y = PANEL_Y,
				.h = BTN_DEFAULT_SIZE, .w = PANEL_BUTTON_WIDTH};
	g_gui.obj[camera_l] = (t_transform){ .rect = rect,
			.state = click, .text = CAMERA_LABEL, .action = camera_l,
			.callback = button_callback, .type = PANEL,
			.color = get_color_from_hex(LAYER_COLOR)};
}

void		init_font(void)
{
	TTF_Init();
	if ((g_gui.title = TTF_OpenFont(FONT_PATH, TITLE_FONT_SIZE)) == NULL)
		rt_raise_error(FONT_ERROR);
	if ((g_gui.subtitle = TTF_OpenFont(FONT_PATH, SUBTITLE_FONT_SIZE)) == NULL)
		rt_raise_error(FONT_ERROR);
	if ((g_gui.body = TTF_OpenFont(MAGMAWAV_CAPS_FONT, BODY_FONT_SIZE)) == NULL)
		rt_raise_error(FONT_ERROR);
}

void		fill_surfaces(void)
{
	render_rect(g_gui.surface, NULL, get_color_from_hex(GUI_BG));
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
			.state = options & RENDER_OBJECTS, .text = OBJECTS_LABEL, .bit = RENDER_OBJECTS,
			.action = obj_btn, .callback = button_callback, .type = OBJECTS_BTN,
			.color = get_color_from_hex((options & RENDER_OBJECTS)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = TEXTURE_Y;
	g_gui.obj[texture_btn] = (t_transform){ .rect = rect, .bit = RENDER_TEXTURES,
			.state = options & RENDER_TEXTURES,  .callback = button_callback,
			.action = texture_btn,   .text = TEXTURE_LABEL, .type = TEXTURES_BTN,
			.color = get_color_from_hex((options & RENDER_TEXTURES)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = ANTI_AL_Y;
	g_gui.obj[aa_btn] = (t_transform){ .rect = rect, .bit = RENDER_ANTI_ALIASING,
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
	g_gui.obj[bfc_btn] = (t_transform){ .rect = rect,
			.bit = RENDER_BACKFACE_CULLING,
			.state = options & RENDER_BACKFACE_CULLING, .text = BACKFACE_LABEL,
			.action = bfc_btn, .callback = button_callback, .type = BFC_BTN,
			.color = get_color_from_hex((options & RENDER_BACKFACE_CULLING)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = IMP_Y;
	rect.x = SECOND_COL_X;
	g_gui.obj[imp_btn] = (t_transform){ .rect = rect, .bit = RENDER_IMPRESSIVE,
			.state = options & RENDER_IMPRESSIVE, .text = IMPRESSIVE_LABEL,
			.action = imp_btn, .callback = button_callback, .type = IMP_BTN,
			.color = get_color_from_hex((options & RENDER_IMPRESSIVE)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
	rect.y = SMOOTH_Y;
	g_gui.obj[smooth_btn] = (t_transform){ .rect = rect,
			.bit = RENDER_BACKFACE_CULLING,
			.state = options & RENDER_BACKFACE_CULLING, .text = SMOOTH_LABEL,
			.action = smooth_btn, .callback = button_callback, .type = SMOOTH_BTN,
			.color = get_color_from_hex((options & RENDER_BACKFACE_CULLING)
			? (BTN_COLOR_CLICK) : (BTN_COLOR_NONACTIVE))};
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

void	init_gui(uint32_t options, uint32_t states, t_scene scene)
{
	g_gui.render_algo = ((options & 0b111) - 1);
	g_gui.panel = camera_l;
	g_gui.obj = rt_safe_malloc(sizeof(t_transform) * (btn_count));
	init_font();
	if ((g_gui.surface = SDL_GetWindowSurface(g_gui.win_tool)) == NULL)
		rt_raise_error(GET_SURFACE_TROUBLE);
	fill_surfaces();
	create_title();
	init_algo_buttons();
	init_object_panel();
	init_other_buttons();
	init_render_options_button(options);
	init_render_states_button(states);
	init_text_box(scene);
	render_all_buttons(scene);
	SDL_UpdateWindowSurface(g_gui.win_tool);
}
