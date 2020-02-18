/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:25:14 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/18 20:59:48 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


SDL_Color activate_color(SDL_Color color)
{
	color.r <<= ACTIVATE;
	color.g <<= ACTIVATE;
	color.b <<= ACTIVATE;
	return (color);
}

SDL_Color disable_color(SDL_Color color)
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
