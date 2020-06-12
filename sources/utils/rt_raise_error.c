/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raise_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_errors.h"

void			rt_raise_error(const char *err_str)
{
	if (err_str)
		ft_printf_fd(STDERR_FILENO, "%s\n", err_str);
	else
		ft_printf_fd(STDERR_FILENO, "UNKNOWN ERROR!\n");
	exit(1);
}
