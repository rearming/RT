/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_window_params.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_WINDOW_PARAMS_H
# define RT_WINDOW_PARAMS_H

# define WIN_TITLE "Dota 5"

# ifdef __APPLE__
#  define WIN_WIDTH 1960
#  define WIN_HEIGHT 1300
# else
#  define WIN_WIDTH 1920
#  define WIN_HEIGHT 1080
# endif

# define WIN_RATIO ((float)WIN_WIDTH / WIN_HEIGHT)
# define INVERSE_WIN_RATIO ((float)WIN_HEIGHT / WIN_WIDTH)
# define D_E_KARMATSKIY (INVERSE_WIN_RATIO * INVERSE_WIN_RATIO)
# define D_I_MAZOHIN (WIN_RATIO * WIN_RATIO)
# define SCALE_WIDTH 1
# define SCALE_HEIGHT 1

#endif
