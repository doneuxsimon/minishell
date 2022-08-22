/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:53:14 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/22 18:24:15 by marvin           ###   ########.fr       */
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

char	*get_cmd2(char **cmd_paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*cmd_paths)
	{
		tmp = ft_strjoin(*cmd_paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		cmd_paths++;
	}
	return (NULL);
}

void	ft_exec_arg_opt(t_list *list, char *cmd, char **cmd_args, int i,
			char **envp)
{
	int	j;

	cmd = get_cmd2(cmd_path, list->ft);
	cmd_args = malloc(sizeof(char *) * (3 + i));
	cmd_args[0] = list->ft;
	cmd_args[1] = list->opt;
	j = 2;
	while (j < i + 2)
	{
		cmd_args[j] = list->arg[j - 2];
		j++;
	}
	cmd_args[j] = NULL;
	if (cmd == NULL)
	{
		printf("command not found \n");
		exit(EXIT_FAILURE);
	}
	execve(cmd, cmd_args, envp);
}

void	ft_exec_arg(t_list *list, char *cmd, char **cmd_arg, int i, char **env)
{
	int	j;

	cmd = get_cmd2(cmd_path, list->ft);
	cmd_arg = malloc(sizeof(char *) * (2 + i));
	cmd_arg[0] = list->ft;
	j = 1;
	while (j < i + 1)
	{
		cmd_arg[j] = list->arg[j - 1];
		j++;
	}
	cmd_arg[j] = NULL;
	if (cmd == NULL)
	{
		printf("command not found \n");
		exit(EXIT_FAILURE);
	}
	execve(cmd, cmd_arg, env);
}

void	ft_exec_opt(t_list *list, char *cmd, char **cmd_args, char **envp)
{
	cmd = get_cmd2(cmd_path, list->ft);
	cmd_args = malloc(sizeof(char *) * 3);
	cmd_args[0] = list->ft;
	cmd_args[1] = list->opt;
	cmd_args[2] = NULL;
	if (cmd == NULL)
	{
		printf("command not found \n");
		exit(EXIT_FAILURE);
	}
	execve(cmd, cmd_args, envp);
}

void	ft_exec_nothing(t_list *list, char * cmd, char **cmd_args, char **envp)
{
	cmd = get_cmd2(cmd_path, list->ft);
	cmd_args = malloc(sizeof(char *) * 2);
	cmd_args[0] = list->ft;
	cmd_args[1] = NULL;
	if (cmd == NULL)
	{
		printf("command not found \n");
		exit(EXIT_FAILURE);
	}
	execve(cmd, cmd_args, envp);
}

int	ft_count_dup(t_list *list)
{
	int	i;

	i = 0;
	if (list->arg)
		{
			while(list->arg[i])
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
}

void	ft_exec(t_list *list, char **cmd_path, char **envp)
{
	char	*cmd;
	char	**cmd_args;
	int		i;
	int		j;

	if (!list->arg && !list->outfile && !list->infile && !list->opt)
	{
		ft_exec_nothing(list, cmd, cmd_args, envp);
	}
	else
	{
		i = ft_count_dup(list);
		if (list->arg && list->opt)
		{
			ft_exec_arg_opt(list, cmd, cmd_args, i, envp);
		}
		else if (!list->opt && list->arg)
		{
			ft_exec_arg(list, cmd, cmd_args, i, envp);
		}
		else if (list->opt && !list->arg)
		{
			ft_exec_opt(list, cmd, cmd_args, envp);
		}
	}
}

int	ft_close_wait(int *piped1, int *piped2, int *pid, int i)
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
	if ((i-1) % 2 == 1)
		waitpid(pid[3], &status, 0);
	return (status);
}

void	ft_fork_0(int *pid, int *piped1, t_list *list,
			char **cmd_path, char ** envp)
{
	int	j;


	pid[0] = fork();
	if (pid[0] == -1)
	printf("error child 1\n");
	if (!pid[0])
	{
	sig(4);
	if (list->infile)
		dup2(list->infile, 0);
	if (dup2(piped1[1], 1) == -1)
		dprintf(2, "jeff1\n");
	close(piped1[0]);
	j = verify_builtins(list, envp, cmd_path);
	if (j == 0)
		ft_exec(list, cmd_path, envp);
	else if (j == 1)
		exit(EXIT_SUCCESS);
	}
}

void	ft_fork_1(int **piped, int *pid, t_list *list, char **cmd_path, char **envp)
{
	close(piped[1][0]);
	close(piped[1][1]);
	pipe(piped[1]);
	list = list->next;
	pid[1] = fork();
	if (pid[1] == -1)
		printf("error child 2\n");
	if (!pid[1])
	{
		sig(4);
		if (dup2(piped1[0], 0) == -1)
			dprintf(2, "jeff2\n");
		if (dup2(piped2[1], 1) == -1)
			dprintf(2, "jeff22\n");
		close(piped[0][1]);
		close(piped[1][0]);
		if (verify_builtins(list, envp, cmd_path) == 0)
			ft_exec(list, cmd_path, envp);
		else if (verify_builtins(list, envp, cmd_path) == 1)
			exit(EXIT_SUCCESS);
	}
}

void	ft_fork_2(int **piped, int *pid, t_list *list, char **cmd_path, char **envp)
{
	close(piped[0][0]);
	close(piped[0][1]);
	pipe(piped[0]);
	pid[2] = fork();
	if (pid[2] == -1)
		printf("error child 2\n");
	if (!pid[2])
	{
		sig(4);
		if (dup2(piped2[0], 0) == -1)
			dprintf(2, "jeff3\n");
		if (count > 1)
		{
			if (dup2(piped1[1], 1) == -1)
				dprintf(2, "jeff3\n");
		}
		close(piped1[0]);
		close(piped2[1]);
		if (count <= 1)
			close(piped1[1]);
		if (verify_builtins(list, envp, cmd_path) == 0)
			ft_exec(list, cmd_path, envp);
		else if (verify_builtins(list, envp, cmd_path) == 1)
			exit(EXIT_SUCCESS);
	}
}

void	ft_fork_3()
{
	pid[3] = fork();
	if (pid[3] == -1)
		printf("error child 2\n");
	if (!pid[3])
	{
		sig(4);
		if (list->outfile)
			dup2(list->outfile, 1);
		if (dup2(piped1[0], 0) == -1)
			dprintf(2, "jeff4\n");
		close(piped1[1]);
		close(piped2[1]);
		close(piped2[0]);

		if (verify_builtins(list, envp, cmd_path) == 0)
			ft_exec(list, cmd_path, envp);
		else if (verify_builtins(list, envp, cmd_path) == 1)
		{
			dprintf(2, "sorti\n");
			exit(EXIT_SUCCESS);
		}
	}
}

void	ft_exec_pipes(t_list *list, char **cmd_path, char **envp, int count)
{
	int	pid[4];
	int	piped1[2];
	int	piped2[2];
	int **piped;
	int	i;
	int	j;
	int	status;

	i = count;
	pid = malloc(sizeof(int) * 4);
	piped = malloc(sizeof(int*) * 2);
	piped[0] = piped1;
	piped[1] = piped2;
	sig(3);
	if (pipe(piped1) < 0)
		return ;
	if (pipe(piped2) < 0)
		return ;
		ft_fork_0(pid, piped1, list, cmd_path, envp);
	count--;
	while (count > 1)
	{
		ft_fork_1(piped, pid, list, cmd_path, envp);
		count--;
		list = list->next;
		ft_fork_2();
		count--;
	}
	if (count > 0)
	{
		list = list->next;
		
	}
	status = ft_close_wait(piped1, piped2, pid, i);
	(*(&g_var))->returned[0] = WEXITSTATUS(status);
}


void	ft_start_exec(t_list *list, char *path, char **envp)
{
	char	**cmd_path;
	int		count;
	int		pid;
	int		j;
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
		{
			sig(4);
			j = verify_builtins(list, envp, cmd_path);
			if (j == 0)
				ft_exec(list, cmd_path, envp);
			else if (j == 1)
				exit(EXIT_SUCCESS);
		}
		waitpid(pid, &status, 0);
		(*(&g_var))->returned[0] = WEXITSTATUS(status);
	}
	else if (count > 1)
	{
		ft_begin(&list);
		ft_exec_pipes(list, cmd_path, envp, count);
	}
}