/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:23:47 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/06 16:34:07 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_exec_nothing(t_list *list, t_exec *exec)
{
	exec->cmd = get_cmd2(exec->cmd_path, list->ft, list);
	exec->cmd_args = malloc(sizeof(char *) * 2);
	if (!exec->cmd_args)
		exit(ft_exit_malloc());
	exec->cmd_args[0] = list->ft;
	exec->cmd_args[1] = NULL;
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
	return (i);
}

t_exec	*ft_init_exec(char **cmd_path, char **envp)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		exit(ft_exit_malloc());
	exec->cmd = NULL;
	exec->cmd_args = NULL;
	exec->cmd_path = cmd_path;
	exec->envp = envp;
	return (exec);
}

void	check_in_outfile(t_list *list)
{
	if (list->infile)
		dup0(list, 0);
	if (list->outfile)
		dup1(list, 0);
}

void	ft_cat_return(t_list *list, int pid)
{
	if (verif_builtin(list) == 2)
		sig(3);
	else
		sig(4);
	g_var->pid[0] = pid;
	g_var->returned[0] = 0;
}
