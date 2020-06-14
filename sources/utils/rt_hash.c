/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long	rt_hash(const char *str)
{
	unsigned long	hash;
	int				c;

	if (!str)
		return (0);
	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}
