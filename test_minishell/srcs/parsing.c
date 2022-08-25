/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/25 16:09:29 by sdoneux          ###   ########.fr       */
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

void	ft_exit(t_list *cmd)
{
	free(cmd);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	ft_compare_n(char *opt)
{
	int	i;

	i = 1;
	if (!opt)
		return (0);
	if (opt[0] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit_pipe(void)
{
	printf("pipe not executed\n");
	return (1);
}

int	ft_exit_fork(void)
{
	printf("fork not executed\n");
	return (1);
}
