/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:58 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:20:02 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		printff(t_tmp *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		printf(" i = %i structure_type = %i type = %i %i\n",
				i, tmp->structure_type, tmp->type, tmp->checker);
		i++;
		tmp = tmp->next;
	}
}

int			main(int argc, char *argv[])
{
	char			*text;
	t_tmp			*tmp;
	json_t			*root;
	json_error_t	error;

	tmp = (t_tmp *)malloc(sizeof(t_tmp));
	if (!(text = read_file(argv[1], 10)))
		return (-1);
	if (init_tmp(tmp) == -1)
		return (-1);
	root = json_loads(text, 0, &error);
	parse_elem(root, tmp);
	printff(tmp);
	json_decref(root);
	free(text);
	return (0);
}
