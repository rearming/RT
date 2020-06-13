/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_color_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"

SDL_Color	activate_color(SDL_Color color)
{
	color.r <<= ACTIVATE;
	color.g <<= ACTIVATE;
	color.b <<= ACTIVATE;
	return (color);
}

SDL_Color	disable_color(SDL_Color color)
{
	color.r >>= ACTIVATE;
	color.g >>= ACTIVATE;
	color.b >>= ACTIVATE;
	return (color);
}

SDL_Color	get_color_from_hex(unsigned int hex)
{
	SDL_Color	color;

	color.r = (hex >> 16) & 0xFF;
	color.g = (hex >> 8) & 0xFF;
	color.b = hex & 0xFF;
	return (color);
}

SDL_Color	get_rgba_from_hex(unsigned int hex)
{
	SDL_Color	color;

	color.r = (hex >> 24) & 0xFF;
	color.g = (hex >> 16) & 0xFF;
	color.b = (hex >> 8) & 0xFF;
	color.a = hex & 0xFF;
	return (color);
}
