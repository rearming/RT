/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"

void		init_cam_text_box(t_scene scene, SDL_Rect rect)
{
	g_gui.obj[c_pos_x] = auto_init_btns_ret(rect, c_pos_x,
			"CPos X", scene.camera.pos.x);
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_pos_y] = auto_init_btns_ret(rect, c_pos_y,
			"CPos y", scene.camera.pos.y);
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_pos_z] = auto_init_btns_ret(rect, c_pos_z,
			"CPos z", scene.camera.pos.z);
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_angle_x] = auto_init_btns_ret(rect, c_angle_x,
			"CAngle x", scene.camera.rotation.x);
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_angle_y] = auto_init_btns_ret(rect, c_angle_y,
			"CAngle y", scene.camera.rotation.y);
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_angle_z] = auto_init_btns_ret(rect, c_angle_z,
			"CAngle z", scene.camera.rotation.z);
	rect.y += BTN_DEFAULT_SIZE;
}

void		init_text_box(t_scene scene)
{
	SDL_Rect rect;

	rect = (SDL_Rect) {
			.x = (WIN_GUI_WIDTH - PANEL_BUTTON_WIDTH) / 2,
			.y = 300,
			.w = TEXT_WIDTH,
			.h = BTN_DEFAULT_SIZE};
	init_cam_text_box(scene, rect);
	g_gui.obj[c_pos_x].param = scene.camera.pos.x;
	g_gui.obj[c_pos_y].param = scene.camera.pos.y;
	g_gui.obj[c_pos_z].param = scene.camera.pos.z;
	g_gui.obj[c_angle_x].param = scene.camera.rotation.x;
	g_gui.obj[c_angle_y].param = scene.camera.rotation.y;
	g_gui.obj[c_angle_z].param = scene.camera.rotation.z;
}
