/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_common_read_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*rt_common_read_file(const char *path, size_t *out_length)
{
	char *buffer;
	FILE *f;
	long length;

	if (!(f = fopen(path, "r")))
		return (NULL);
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = rt_safe_malloc(length);
	if (fread(buffer, 1, length, f) < (size_t)length)
		return (NULL);
	fclose(f);
	if (out_length)
		*out_length = length;
	return (buffer);
}
