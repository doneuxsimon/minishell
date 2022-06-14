/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:53:14 by sdoneux           #+#    #+#             */
/*   Updated: 2022/06/14 18:12:18 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

int	ft_exec(t_list *list, char **cmd_path, char **envp)
{
	int	pid;
	char *cmd;
	char **cmd_args;

	pid = fork();
	if (!pid)
	{
		if (!list->arg)
		{
			cmd = get_cmd2(cmd_path, list->ft);
			cmd_args = malloc(sizeof(char *) * 2);
			cmd_args[0] = list->ft;
			cmd_args[1] = list->opt;
			if (cmd == NULL)
			{
				printf("command not found \n");
				exit(EXIT_FAILURE);
			}
			execve(cmd, cmd_args, envp);
		}
	}
	else if (pid)
	{
		waitpid(pid, NULL, 0);
	}

	return(pid);
}

// void	ft_exec_simple_pipe(t_list *list, char ** cmd_path)
// {
// 	int	pid;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{

// 	}

// }

// void	ft_exec_double_pipe(t_list *list, char ** cmd_path)
// {
// 	int	pid;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{

// 	}

// }

// void	ft_exec_simple_and(t_list *list, char ** cmd_path)
// {
// 	int	pid;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{

// 	}

// }

// void	ft_exec_double_and(t_list *list, char ** cmd_path)
// {
// 	int	pid;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{
		
// 	}

// }

void	ft_start_exec(t_list *list, char *path, char **envp)
{
	char **cmd_path;
	int	count;
	int	pid;

	count = ft_count_forks(list);
	cmd_path = ft_split(path, ':');
	while (count-- >= 0)
		pid = ft_exec(list, cmd_path, envp);
}