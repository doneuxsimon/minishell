/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:21:56 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/13 15:38:49 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_exec(t_list *list, char **cmd_path, char **envp)
{
	int		i;
	t_exec	*exec;

	i = 0;
	exec = ft_init_exec(cmd_path, envp);
	if (!list->arg && !list->opt)
		ft_exec_nothing(list, exec);
	else
	{
		i = ft_count_dup(list, i);
		if (list->arg && list->opt)
			ft_exec_arg_opt(list, exec, i);
		else if (!list->opt && list->arg)
			ft_exec_arg(list, exec, i);
		else if (list->opt && !list->arg)
			ft_exec_opt(list, exec);
	}
	free(exec);
}

void	ft_close_wait(int *piped1, int *piped2, int *pid, int i)
{
	int	status;

	close(piped1[0]);
	close(piped1[1]);
	close(piped2[0]);
	close(piped2[1]);
	waitpid(pid[0], &status, 0);
	if (i > 2)
	{
		waitpid(pid[1], &status, 0);
		waitpid(pid[2], &status, 0);
	}
	if ((i - 1) % 2 == 1)
		waitpid(pid[3], &status, 0);
	if (g_var->returned[0] != 130 && g_var->returned[0] != 131)
		g_var->returned[0] = WEXITSTATUS(status);
}

void	ft_fork_0(t_list *list, t_exec_pipe *exec)
{
	exec->pid[0] = fork();
	if (exec->pid[0] == -1)
		exit(ft_exit_fork());
	if (!exec->pid[0])
	{
		sig(5);
		check_in_outfile(list);
		if (dup1(list, exec->piped1[1]) == -1)
			exit(ft_exit_pipe());
		close(exec->piped1[0]);
		if (verify_builtins(list, exec->envp) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else
			exit(EXIT_SUCCESS);
	}
	else
		ft_cat_return(list, exec->pid[0]);
}

void	ft_fork_1(t_list **list, t_exec_pipe *exec)
{
	close(exec->piped2[0]);
	close(exec->piped2[1]);
	if (pipe(exec->piped2) < 0)
		ft_exit_pipe();
	(*list) = (*list)->next;
	exec->pid[1] = fork();
	if (exec->pid[1] == -1)
		ft_exit_fork();
	if (!exec->pid[1])
	{
		sig(5);
		check_in_outfile(*list);
		if (dup0(*list, exec->piped1[0]) == -1)
			exit(ft_exit_pipe());
		if (dup1(*list, exec->piped2[1]) == -1)
			exit(ft_exit_pipe());
		close(exec->piped1[1]);
		close(exec->piped2[0]);
		if (verify_builtins((*list), exec->envp) == 0)
			ft_exec((*list), exec->cmd_path, exec->envp);
		else
			exit(EXIT_SUCCESS);
	}
	else
		ft_cat_return(*list, exec->pid[1]);
}

void	ft_fork_2(t_list *list, t_exec_pipe *exec)
{
	ft_close_pipe(exec);
	exec->pid[2] = fork();
	if (exec->pid[2] == -1)
		exit(ft_exit_fork());
	if (!exec->pid[2])
	{
		check_in_outfile2(list);
		if (dup0(list, exec->piped2[0]) == -1)
			exit(ft_exit_pipe());
		if (exec->count > 1)
		{
			if (dup1(list, exec->piped1[1]) == -1)
				exit(ft_exit_pipe());
		}
		close(exec->piped1[0]);
		close(exec->piped2[1]);
		if (exec->count <= 1)
			close(exec->piped1[1]);
		if (verify_builtins(list, exec->envp) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else
			exit(EXIT_SUCCESS);
	}
	else
		ft_cat_return(list, exec->pid[2]);
}
