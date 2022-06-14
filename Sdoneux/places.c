/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   places.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:01:03 by sdoneux           #+#    #+#             */
/*   Updated: 2022/06/14 17:01:40 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_end(t_list **stack)
{
	if (*stack && (*stack)->next)
	{
		while ((*stack)->next != NULL)
		{
			(*stack) = (*stack)->next;
		}
	}
}

void	ft_begin(t_list **stack)
{
	if (*stack && (*stack)->before)
	{
		while ((*stack)->before != NULL)
		{
			(*stack) = (*stack)->before;
		}
	}
}