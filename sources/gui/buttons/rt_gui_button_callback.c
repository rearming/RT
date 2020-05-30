/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_render_callback.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 18:52:27 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/20 15:55:31 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"



bool		handle_button(t_transform *btn, t_rt *rt)
{
	if (btn->type & RENDER_BTN)
	{
		btn->state = click;
		change_render_algo(btn->action, rt);
		g_gui.render_algo = btn->action;
		return (true);
	}
	else if (btn->type & SCREENSHOT)
	{
		if (SCREENSHOT_FORMAT == BMP)
			create_screenshot_bmp();
		else if (SCREENSHOT_FORMAT == PNG)
			create_screenshot_png();
		else if (SCREENSHOT_FORMAT == JPG)
			create_screenshot_jpg();
		else
			create_screenshot_bmp();
		return (true);
	}
	else if (btn->type & PANEL)
	{
		btn->state = click;
		g_gui.panel = btn->action;
		return (true);
	}
	return (false);
}

bool		handle_textbox(t_transform *btn, SDL_Event *event, t_rt *rt)
{
	if (event->type == SDL_MOUSEMOTION)
		return (false);
	if (event->type == SDL_MOUSEBUTTONDOWN && check_click(event, btn->rect))
	{
//		btn->color = get_color_from_hex(WHITE);
		btn->focus = true;
//		printf("btn %s pressed\n", btn->text);
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && btn->focus &&!check_click(event, btn->rect))
	{
		btn->focus = false;
//		btn->color = get_color_from_hex(BLACK);
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && check_hover(event, btn->rect))
	{
//		ft_strcat(btn->field, "teSTing");
		printf("try to change btn %s \n", btn->text);
		return (true);
	}
	return (false);
}

bool		handle_movement(t_transform *btn, SDL_Event *event, t_scene scene)
{
	bool res;

	res = false;
	if (btn->action == c_pos_x)
		res |= is_positions_changed(c_pos_x, scene.camera.pos.x);
	if (btn->action == c_pos_y)
		res |= is_positions_changed(c_pos_y, scene.camera.pos.y);
	if (btn->action == c_pos_z)
		res |= is_positions_changed(c_pos_z, scene.camera.pos.z);
	if (btn->action == c_angle_x)
		res |= is_positions_changed(c_angle_x, scene.camera.rotation.x);
	if (btn->action == c_angle_y)
		res |= is_positions_changed(c_angle_y, scene.camera.rotation.y);
	if (btn->action == c_angle_z)
		res |= is_positions_changed(c_angle_z, scene.camera.rotation.z);
	return (res);
}

bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt)
{
	if (btn->type & TEXT_BOX)
	{
		int test;

		test = is_positions_changed(c_pos_x, rt->scene.camera.pos.x);

		return (handle_textbox(btn, event, rt) || handle_movement(btn, event, rt->scene));
	}
	if (event->type != SDL_MOUSEBUTTONDOWN && event->type != SDL_MOUSEMOTION)
		return (false);
	if (event->type == SDL_MOUSEMOTION && check_hover(event, btn->rect) && btn->state != click)
	{
		btn->state = hover;
		return (true);
	}
	if (event->type == SDL_MOUSEMOTION && !check_hover(event, btn->rect) && btn->state == hover)
	{
		btn->state = non_event;
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && btn->state == hover && check_click(event, btn->rect))
		return (handle_button(btn, rt));
	return (false);
}