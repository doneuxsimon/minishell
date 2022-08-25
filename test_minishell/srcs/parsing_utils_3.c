/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:51:03 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/25 15:51:31 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_compare_n2(t_list *list)
{
	int	i;
	int	n;

	n = 1;
	i = 1;
	if (!list->opt)
		return (0);
	if (list->opt[0] != '-')
		n = 0;
	while (list->opt[i])
	{
		if (list->opt[i] != 'n')
			n = 0;
		i++;
	}
	if (n == 0)
	{
		write(2, list->opt, ft_strlen(list->opt));
		if (!list->arg)
			write(2, "\n", 1);
		else
			write(2, " ", 1);
	}
	return (n);
}

int	ft_skip_n(t_list *list, int i, int n)
{
	while (ft_compare_n(list->arg[i]) && n)
	{
		n = ft_compare_n(list->arg[i]);
		i++;
	}
	return (i);
}
