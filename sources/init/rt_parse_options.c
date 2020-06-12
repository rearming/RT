/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_init.h"

uint32_t	parse_option(const char *option)
{
	if (ft_strequ(option, OPTION_REGENERATE_KD_TREE))
		return (INIT_KD_REGENERATE);
	else
		ft_printf("[warning] invalid option \"%s\"\n", option);
	return (0);
}

uint32_t	rt_parse_init_options(char **options, int options_num,
		int first_option)
{
	uint32_t	bit_options;
	int			i;

	bit_options = 0;
	i = first_option;
	while (i < options_num)
	{
		bit_options |= parse_option(options[i]);
		i++;
	}
	return (bit_options);
}
