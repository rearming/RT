/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:20:14 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:20:21 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*read_file(const char *argv, int buff_size)
{
	int		ret;
	char	buf[buff_size];
	char	*tmp;
	char	*result;
	int		fd;

	if (!(fd = open(argv, O_RDONLY)))
		rt_raise_error(ERR_INV_FILE);
	if (fd < 0 || !(result = ft_strnew(1)))
		rt_raise_error(ERR_INV_FILE);
	while ((ret = read(fd, buf, buff_size)) > 0 && result)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(result, buf);
		free(result);
		if (!tmp)
			rt_raise_error(ERR_MALLOC);
		result = tmp;
	}
	return (result);
}