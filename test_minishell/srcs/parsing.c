/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/23 18:28:40 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_env(int *i)
{
	(*i) = 1;
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		printf("%s=%s\n", g_var->name, g_var->value);
		g_var = g_var->next;
	}
}

void	ft_exit(void)
{
	printf("\nexit\n");
	exit(EXIT_SUCCESS);
}

int	ft_compare_n(t_list *list)
{
	int	i;

	i = 1;
	if (!list->opt)
		return (0);
	if (list->opt[0] != '-')
		return (0);
	while (list->opt[i])
	{
		if (list->opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
