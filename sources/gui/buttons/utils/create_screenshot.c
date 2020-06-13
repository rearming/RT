/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_screenshot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

SDL_Surface	*get_pixels_from_surface(void)
{
	SDL_Surface		*surface;
	const Uint32	format = SDL_PIXELFORMAT_ABGR8888;
	const SDL_Rect	win = get_window_data();

	surface = SDL_CreateRGBSurfaceWithFormat(0, win.w, win.h,
			32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels,
			surface->pitch);
	return (surface);
}

void		create_screenshot_bmp(void)
{
	SDL_Surface	*surface;
	char		*file;

	surface = get_pixels_from_surface();
	file = name_generator(".bmp");
	SDL_SaveBMP(surface, file);
	ft_strdel(&file);
	SDL_FreeSurface(surface);
}

void		create_screenshot_png(void)
{
	char			*file;
	SDL_Color		*color_map;
	SDL_Surface		*surface;
	const SDL_Rect	win = get_window_data();

	surface = get_pixels_from_surface();
	color_map = (SDL_Color *)surface->pixels;
	file = name_generator(".png");
	stbi_write_png(file, win.w, win.h, 4,
			color_map, win.w * 4);
	ft_strdel(&file);
	SDL_FreeSurface(surface);
}

void		create_screenshot_jpg(void)
{
	char			*file;
	SDL_Color		*color_map;
	SDL_Surface		*surface;
	const SDL_Rect	win = get_window_data();

	surface = get_pixels_from_surface();
	color_map = (SDL_Color *)surface->pixels;
	file = name_generator(".jpg");
	stbi_write_jpg(file, win.w, win.h, 4, color_map, 100);
	ft_strdel(&file);
	SDL_FreeSurface(surface);
}
