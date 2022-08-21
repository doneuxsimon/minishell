/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:53:14 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/21 17:34:42 by marvin           ###   ########.fr       */
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
		list =list->next;
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
	return(NULL);
}

int	ft_exec(t_list *list, char **cmd_path, char **envp)
{
	char	*cmd;
	char	**cmd_args;
	int		i;
	int		j;

	if (!list->arg && !list->outfile && !list->infile && !list->opt)
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
		if (cmd)
			dprintf(2, "%s\n", cmd);
		return(execve(cmd, cmd_args, envp));
	}
	else
	{
		if (list->arg)
		{
			i = 0;
			while(list->arg[i])
				i++;
		}
		if (!list->piped[0])
		{
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
		if (list->arg && list->opt)
		{
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
		}
		else if (!list->opt && list->arg)
		{
			cmd = get_cmd2(cmd_path, list->ft);
			cmd_args = malloc(sizeof(char *) * (2 + i));
			cmd_args[0] = list->ft;
			j = 1;
			while (j < i + 1)
			{
				cmd_args[j] = list->arg[j - 1];
				j++;
			}
			cmd_args[j] = NULL;
		}
		else if (list->opt && !list->arg)
		{
			cmd = get_cmd2(cmd_path, list->ft);
			cmd_args = malloc(sizeof(char *) * (2 + i));
			cmd_args[0] = list->ft;
			cmd_args[1] = list->opt;
			cmd_args[2] = NULL;
		}
		else 
		{
			cmd = get_cmd2(cmd_path, list->ft);
			cmd_args = malloc(sizeof(char *) * 2);
			cmd_args[0] = list->ft;
			cmd_args[1] = NULL;
		}
		if (cmd == NULL)
		{
			printf("command not found \n");
			exit(EXIT_FAILURE);
		}
		dprintf(2, "%s\n", cmd);
		return(execve(cmd, cmd_args, NULL));
	}
}


 void	ft_exec_pipes(t_list *list, char **cmd_path, char **envp, int count)
{
	int	pid1;
	int	pid2;
	int	pid3;
	int	pid4;
	int	piped1[2];
	int	piped2[2];
	int	i;
	int	j;
	int	status;

	i = count;
	sig(3);
	if (pipe(piped1) < 0)
		return ;
	if (pipe(piped2) < 0)
		return ;
	pid1 = fork();
	if (pid1 == -1)
		printf("error child 1\n");
	if (!pid1)
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
		{
			dprintf(2, "sorti\n");
			exit(EXIT_SUCCESS);
		}
	}
	count--;
	while (count > 1)
	{
		close(piped2[0]);
		close(piped2[1]);
		pipe(piped2);
		list = list->next;
		pid2 = fork();
		if (pid2 == -1)
			printf("error child 2\n");
		if (!pid2)
		{
			sig(4);
			if (dup2(piped1[0], 0) == -1)
				dprintf(2, "jeff2\n");
			if (dup2(piped2[1], 1) == -1)
				dprintf(2, "jeff22\n");
			close(piped1[1]);
			close(piped2[0]);
			j = verify_builtins(list, envp, cmd_path);
			if (j == 0)
				ft_exec(list, cmd_path, envp);
			else if (j == 1)
			{
				dprintf(2, "sorti\n");
				exit(EXIT_SUCCESS);
			}
		}
		close(piped1[0]);
		close(piped1[1]);
		pipe(piped1);
		count--;
		list = list->next;
		pid3 = fork();
		if (pid3 == -1)
			printf("error child 2\n");
		if (!pid3)
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
			j = verify_builtins(list, envp, cmd_path);
			if (j == 0)
				ft_exec(list, cmd_path, envp);
			else if (j == 1)
			{
				dprintf(2, "sorti\n");
				exit(EXIT_SUCCESS);
			}
		}
		count--;
	}
	if (count > 0)
	{
		list = list->next;
		pid4 = fork();
		if (pid4 == -1)
			printf("error child 2\n");
		if (!pid4)
		{
			sig(4);
			if (list->outfile)
				dup2(list->outfile, 1);
			if (dup2(piped1[0], 0) == -1)
				dprintf(2, "jeff4\n");
			close(piped1[1]);
			close(piped2[1]);
			close(piped2[0]);
			j = verify_builtins(list, envp, cmd_path);
			if (j == 0)
				ft_exec(list, cmd_path, envp);
			else if (j == 1)
			{
				dprintf(2, "sorti\n");
				exit(EXIT_SUCCESS);
			}
		}
	}
	close(piped1[0]);
	close(piped1[1]);
	close(piped2[0]);
	close(piped2[1]);
	waitpid(pid1, &status, 0);
	if (i > 2)
	{
		waitpid(pid2, &status, 0);
		waitpid(pid3, &status, 0);
	}
	if ((i-1) % 2 == 1)
		waitpid(pid4, &status, 0);
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