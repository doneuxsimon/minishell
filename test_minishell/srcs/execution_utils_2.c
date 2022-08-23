/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:21:56 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/23 18:23:27 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_exec(t_list *list, char **cmd_path, char **envp)
{
	int		i;
	t_exec	*exec;

	i = 0;
	exec = ft_init_exec(cmd_path, envp);
	if (!list->arg && !list->outfile && !list->infile && !list->opt)
	{
		ft_exec_nothing(list, exec);
	}
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
	g_var->returned[0] = WEXITSTATUS(status);
}

void	ft_fork_0(t_list *list, t_exec_pipe *exec)
{
	exec->pid[0] = fork();
	if (exec->pid[0] == -1)
		printf("error child 1\n");
	if (!exec->pid[0])
	{
		sig(4);
		if (list->infile)
			dup2(list->infile, 0);
		if (dup2(exec->piped1[1], 1) == -1)
			dprintf(2, "jeff1\n");
		close(exec->piped1[0]);
		if (verify_builtins(list, exec->envp, exec->cmd_path) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else if (verify_builtins(list, exec->envp, exec->cmd_path) == 1)
			exit(EXIT_SUCCESS);
	}
}

void	ft_fork_1(t_list *list, t_exec_pipe *exec)
{
	close(exec->piped2[0]);
	close(exec->piped2[1]);
	pipe(exec->piped2);
	list = list->next;
	exec->pid[1] = fork();
	if (exec->pid[1] == -1)
		printf("error child 2\n");
	if (!exec->pid[1])
	{
		sig(4);
		if (dup2(exec->piped1[0], 0) == -1)
			dprintf(2, "jeff2\n");
		if (dup2(exec->piped2[1], 1) == -1)
			dprintf(2, "jeff22\n");
		close(exec->piped1[1]);
		close(exec->piped2[0]);
		if (verify_builtins(list, exec->envp, exec->cmd_path) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else if (verify_builtins(list, exec->envp, exec->cmd_path) == 1)
			exit(EXIT_SUCCESS);
	}
}

void	ft_fork_2(t_list *list, t_exec_pipe *exec)
{
	close(exec->piped1[0]);
	close(exec->piped1[1]);
	pipe(exec->piped1);
	exec->pid[2] = fork();
	if (exec->pid[2] == -1)
		printf("error child 2\n");
	if (!exec->pid[2])
	{
		sig(4);
		if (dup2(exec->piped2[0], 0) == -1)
			dprintf(2, "jeff3\n");
		if (exec->count > 1)
		{
			if (dup2(exec->piped1[1], 1) == -1)
				dprintf(2, "jeff3\n");
		}
		close(exec->piped1[0]);
		close(exec->piped2[1]);
		if (exec->count <= 1)
			close(exec->piped1[1]);
		if (verify_builtins(list, exec->envp, exec->cmd_path) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else if (verify_builtins(list, exec->envp, exec->cmd_path) == 1)
			exit(EXIT_SUCCESS);
	}
}