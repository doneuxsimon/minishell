/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:19:52 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/23 18:23:30 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_fork_3(t_list *list, t_exec_pipe *exec)
{
	exec->pid[3] = fork();
	if (exec->pid[3] == -1)
		printf("error child 2\n");
	if (!exec->pid[3])
	{
		sig(4);
		if (list->outfile)
			dup2(list->outfile, 1);
		if (dup2(exec->piped1[0], 0) == -1)
			dprintf(2, "jeff4\n");
		close(exec->piped1[1]);
		close(exec->piped2[1]);
		close(exec->piped2[0]);
		if (verify_builtins(list, exec->envp, exec->cmd_path) == 0)
			ft_exec(list, exec->cmd_path, exec->envp);
		else if (verify_builtins(list, exec->envp, exec->cmd_path) == 1)
		{
			dprintf(2, "sorti\n");
			exit(EXIT_SUCCESS);
		}
	}
}

t_exec_pipe	*ft_init_exec_pipe(char **cmd_path, char **envp, int count)
{
	t_exec_pipe	*piped;

	piped = malloc(sizeof(t_exec_pipe));
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
	i = count;
	sig(3);
	ft_fork_0(list, exec);
	count--;
	while (count > 1)
	{
		ft_fork_1(list, exec);
		count--;
		list = list->next;
		ft_fork_2(list, exec);
		count--;
	}
	if (count > 0)
	{
		list = list->next;
		ft_fork_3(list, exec);
	}
	ft_close_wait(exec->piped1, exec->piped2, exec->pid, i);
}

void	ft_start_exec_2(char **envp, char **cmd_path, t_list *list)
{
	int	j;

	sig(4);
	j = verify_builtins(list, envp, cmd_path);
	if (j == 0)
		ft_exec(list, cmd_path, envp);
	else if (j == 1)
		exit(EXIT_SUCCESS);
}

void	ft_start_exec(t_list *list, char *path, char **envp)
{
	char	**cmd_path;
	int		count;
	int		pid;
	int		status;

	if (list->ft == NULL)
		return ;
	count = ft_count_forks(list);
	cmd_path = ft_split(path, ':');
	if (count == 1)
	{
		sig(3);
		pid = fork();
		if (!pid)
			ft_start_exec_2(envp, cmd_path, list);
		waitpid(pid, &status, 0);
		g_var->returned[0] = WEXITSTATUS(status);
	}
	else if (count > 1)
	{
		ft_begin(&list);
		ft_exec_pipes(list, cmd_path, envp, count);
	}
}