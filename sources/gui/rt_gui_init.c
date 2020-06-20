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

void		init_gui(uint32_t options, uint32_t states, t_scene scene)
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
