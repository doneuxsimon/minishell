/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:53:14 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/12 18:18:59 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_count_forks(t_list *list)
{
	int	i;

	i = 0;
	ft_begin(&list);
	while (list->next)
	{
		list = list->next;
		i++;
	}
	i++;
	return (i);
}

char	*get_cmd2(char **cmd_paths, char *cmd, t_list *list)
{
	char	*str;

	str = get_cmd2_utils(cmd_paths, cmd);
	if (cmd[0] != '/' && str)
		return (str);
	free(str);
	if (cmd[0] == '/')
	{
		if (!cmd[1] && cmd[0] == '/')
		{
			printf("minishell: /: Is a directory\n");
			return (NULL);
		}
		if (access(cmd, 0) == 0)
			return (cmd);
		else
		{
			printf("minishell: %s: No such file or directory\n", cmd);
			return (NULL);
		}
	}
	if (!verif_builtin(list))
		printf("minishell: %s: Command not found\n", list->ft);
	return (NULL);
}

void	ft_exec_arg_opt(t_list *list, t_exec *exec, int i)
{
	int	j;

	exec->cmd = get_cmd2(exec->cmd_path, list->ft, list);
	exec->cmd_args = malloc(sizeof(char *) * (3 + i));
	if (!exec->cmd_args)
		exit(ft_exit_malloc());
	exec->cmd_args[0] = list->ft;
	exec->cmd_args[1] = list->opt;
	j = 2;
	while (j < i + 2)
	{
		exec->cmd_args[j] = list->arg[j - 2];
		j++;
	}
	exec->cmd_args[j] = NULL;
	execve(exec->cmd, exec->cmd_args, exec->envp);
}

void	ft_exec_arg(t_list *list, t_exec *exec, int i)
{
	int	j;

	exec->cmd = get_cmd2(exec->cmd_path, list->ft, list);
	exec->cmd_args = malloc(sizeof(char *) * (2 + i));
	if (!exec->cmd_args)
		exit(ft_exit_malloc());
	exec->cmd_args[0] = list->ft;
	j = 1;
	while (j < i + 1)
	{
		exec->cmd_args[j] = list->arg[j - 1];
		j++;
	}
	exec->cmd_args[j] = NULL;
	execve(exec->cmd, exec->cmd_args, exec->envp);
}

void	ft_exec_opt(t_list *list, t_exec *exec)
{
	exec->cmd = get_cmd2(exec->cmd_path, list->ft, list);
	exec->cmd_args = malloc(sizeof(char *) * 3);
	if (!exec->cmd_args)
		exit(ft_exit_malloc());
	exec->cmd_args[0] = list->ft;
	exec->cmd_args[1] = list->opt;
	exec->cmd_args[2] = NULL;
	execve(exec->cmd, exec->cmd_args, exec->envp);
}
