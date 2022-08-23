/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:23:47 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/23 18:24:26 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_exec_nothing(t_list *list, t_exec *exec)
{
	exec->cmd = get_cmd2(exec->cmd_path, list->ft);
	exec->cmd_args = malloc(sizeof(char *) * 2);
	exec->cmd_args[0] = list->ft;
	exec->cmd_args[1] = NULL;
	if (exec->cmd == NULL)
	{
		printf("command not found \n");
		exit(EXIT_FAILURE);
	}
	execve(exec->cmd, exec->cmd_args, exec->envp);
}

int	ft_count_dup(t_list *list, int i)
{
	i = 0;
	if (list->arg)
	{
		while (list->arg[i])
			i++;
	}
	if (list->infile)
	{
		if (list->infile < 0)
		{
			perror("INFILE");
			exit(EXIT_SUCCESS);
		}
		dup2(list->infile, 0);
	}
	if (list->outfile)
	{
		if (list->outfile < 0)
		{
			perror("OUTFILE");
			exit(EXIT_SUCCESS);
		}
		dup2(list->outfile, 1);
	}
	return (i);
}

t_exec	*ft_init_exec(char **cmd_path, char **envp)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->cmd = NULL;
	exec->cmd_args = NULL;
	exec->cmd_path = cmd_path;
	exec->envp = envp;
	return (exec);
}
