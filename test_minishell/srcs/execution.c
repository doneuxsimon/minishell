/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:53:14 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/03 19:36:25 by sdoneux          ###   ########.fr       */
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
	return (NULL);
}

void	ft_exec(t_list *list, char **cmd_path, char **envp)
{
	// int	pid;
	char *cmd;
	char **cmd_args;
	int	i;
	int	j;

	// pid = fork();
	// if (!pid)
	// {
		if (!list->arg && !list->outfile && !list->infile && !list->opt)
		{
			cmd = get_cmd2(cmd_path, list->ft);
			cmd_args = malloc(sizeof(char *) * 2);
			cmd_args[0] = list->ft;
			cmd_args[1] = NULL;
			printf("jeff435\n");
			if (cmd == NULL)
			{
				printf("command not found \n");
				exit(EXIT_FAILURE);
			}
			printf("bla %d\n", list->piped[0]);
			execve(cmd, cmd_args, envp);
		}
		else if (list->arg || list->outfile || list->infile || list->opt)
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
			
			execve(cmd, cmd_args, NULL);
			if (errno)
			{
				printf("%s\n", strerror(errno));
			}
			printf("bla\n");
		}
	// }
	// else if (pid)
	// {
	// 	waitpid(pid, NULL, 0);
	// }
}

 void	ft_exec_simple_pipe(t_list *list, char **cmd_path, char **envp)
{
	int	pid1;
	int pid2;
	//int tmp = dup(0);

	if (pipe(list->piped) < 0)
		return ;
	pid1 = fork();
	if (pid1 == -1)
		printf("error child 1\n");
	if (!pid1)
	{
		if (list->infile)
			dup2(list->infile, 0);
		if (dup2(list->piped[1], 1) == -1)
			printf("jeff1\n");
		close(list->piped[0]);
		printf("adress1:%p\n", &list->piped[1]);
		ft_exec(list, cmd_path, envp);
	}
	waitpid(pid1, NULL, 0);
	list = list->next;
	pid2 = fork();
	if (pid2 == -1)
		printf("error child 2\n");
	if (!pid2)
	{
		if (list->outfile)
			dup2(list->outfile, 1);
		if (dup2(list->piped[0], 0) == -1)
			printf("jeff2\n");
		close(list->piped[1]);
		printf("adress2:%p\n", &list->piped[0]);
		ft_exec(list, cmd_path, envp);
		//dup2(tmp, 0);
	}
	// close(list->piped[0]);
	// close(list->piped[1]);
	waitpid(pid2, NULL, 0);
	printf("ok\n");
}

void	ft_start_exec(t_list *list, char *path, char **envp)
{
	char **cmd_path;
	int	count;
	int pid;

	count = ft_count_forks(list);
	cmd_path = ft_split(path, ':');
	if (count == 1)
	{
		pid = fork();
		if (!pid)
			ft_exec(list, cmd_path, envp);
		waitpid(pid, NULL, 0);
	}
	else if (count == 2)
	{
		ft_begin(&list);
		ft_exec_simple_pipe(list, cmd_path, envp);
	}
}