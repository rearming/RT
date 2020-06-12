/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:32:44 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 13:32:44 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INIT_H
# define RT_INIT_H

# define OPTION_REGENERATE_KD_TREE "--regenerate"

typedef enum		e_init_options
{
	INIT_NONE = 0x0,
	INIT_KD_REGENERATE = (1 << 0),
}					t_init_options;

#endif
