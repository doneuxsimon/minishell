/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   places.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:01:03 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/01 17:26:09 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_end(t_list **stack)
{
	if (*stack && (*stack)->next)
	{
		while ((*stack)->next->pos != 0)
		{
			(*stack) = (*stack)->next;
		}
	}
}

void	ft_begin(t_list **stack)
{
	if (*stack && (*stack)->before)
	{
		while ((*stack)->pos != 0)
		{
			(*stack) = (*stack)->before;
		}
	}
}