/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/06 19:25:05 by sdoneux          ###   ########.fr       */
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
	if (cmd->arg && cmd->arg[0])
	{
		if (is_digitt(cmd->arg[0]) == 1)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->arg[0]);
			free_all(&cmd, 0);
			exit(2);
		}
		else if (is_digitt(cmd->arg[0]) == 0 && cmd->arg[1])
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
		}
		else
			ft_exit_utils(cmd);
	}
	else
	{
		printf("exit\n");
		free_all(&cmd, 0);
		exit(EXIT_SUCCESS);
	}
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
