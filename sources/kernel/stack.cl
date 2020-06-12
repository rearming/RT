/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool						ft_stack_push(t_stack *stack, t_kd_traverse_helper helper)
{
	stack->last_elem++;
	stack->helpers[stack->last_elem] = helper;
	return (true);
}

t_kd_traverse_helper		ft_stack_pop(t_stack *stack)
{
	return (stack->helpers[stack->last_elem--]);
}

t_kd_traverse_helper		ft_stack_peek(t_stack *stack)
{
	return (stack->helpers[stack->last_elem]);
}
