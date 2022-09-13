/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:19:52 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/13 15:36:30 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_fork_3(t_list *list, t_exec_pipe *exec)
{
	exec->pid[3] = fork();
	if (exec->pid[3] == -1)
		exit(ft_exit_fork());
	if (!exec->pid[3])
	{
		sig(5);
		check_in_outfile(list);
		if (dup0(list, exec->piped1[0]) == -1)
			exit(ft_exit_pipe());
		if (close(exec->piped1[1]) < 0)
			exit(ft_exit_close());
		if (close(exec->piped2[1]) < 0)
			exit(ft_exit_close());
		if (close(exec->piped2[0]) < 0)
			exit(ft_exit_close());
		if (verify_builtins(list, exec->envp) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else
			exit(EXIT_SUCCESS);
	}
	else
		ft_cat_return(list, exec->pid[3]);
}

t_exec_pipe	*ft_init_exec_pipe(char **cmd_path, char **envp, int count)
{
	t_exec_pipe	*piped;

	piped = malloc(sizeof(t_exec_pipe));
	if (!piped)
		exit(ft_exit_pipe());
	piped->cmd_path = cmd_path;
	piped->count = count;
	if (pipe(piped->piped1) < 0)
		return (NULL);
	if (pipe(piped->piped2) < 0)
		return (NULL);
	piped->envp = envp;
	return (piped);
}

void	ft_exec_pipes(t_list *list, char **cmd_path, char **envp, int count)
{
	int			i;
	t_exec_pipe	*exec;

	exec = ft_init_exec_pipe(cmd_path, envp, count);
	if (!exec)
		return ;
	i = exec->count;
	sig(3);
	ft_fork_0(list, exec);
	exec->count--;
	while (exec->count > 1)
	{
		ft_fork_1(&list, exec);
		exec->count--;
		list = list->next;
		ft_fork_2(list, exec);
		exec->count--;
	}
	if (exec->count > 0)
	{
		list = list->next;
		ft_fork_3(list, exec);
	}
	ft_close_wait(exec->piped1, exec->piped2, exec->pid, i);
	free(exec);
}

void	ft_start_exec_2(char **envp, char **cmd_path, t_list *list, int pid)
{
	int	j;
	int	status;

	j = 0;
	pid = fork();
	if (pid < 0)
		ft_exit_fork();
	if (!pid)
	{
		sig(5);
		check_in_outfile(list);
		j = verify_builtins(list, envp);
		if (j == 0)
			ft_exec(list, cmd_path, envp);
		else if (j == 1)
			exit(EXIT_SUCCESS);
	}
	else
	{
		ft_cat_return(list, pid);
		waitpid(pid, &status, 0);
	}
	if (g_var->returned[0] != 130 && g_var->returned[0] != 131)
		g_var->returned[0] = WEXITSTATUS(status);
}

void	ft_start_exec(t_list *list, char *path, char **envp)
{
	char	**cmd_path;
	int		count;
	int		pid;

	pid = 0;
	if (list->ft == NULL)
		return ;
	count = ft_count_forks(list);
	cmd_path = ft_split(path, ':');
	if (!cmd_path)
	{
		perror("split in start_exec");
		exit(1);
	}
	ft_begin(&list);
	if (command_exist(list, cmd_path) == 0)
	{
		ft_freed(cmd_path);
		return ;
	}
	if (count == 1)
		ft_start_exec_2(envp, cmd_path, list, pid);
	if (count > 1)
		ft_exec_pipes(list, cmd_path, envp, count);
	ft_freed(cmd_path);
}
