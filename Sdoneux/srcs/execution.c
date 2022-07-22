/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:53:14 by sdoneux           #+#    #+#             */
/*   Updated: 2022/07/22 17:50:47 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/test.h"

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
	int	pid;
	char *cmd;
	char **cmd_args;
	int	i;
	int	j;

	pid = fork();
	if (!pid)
	{
		if (!list->arg && !list->outfile && !list->infile)
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
		else if (list->arg || list->outfile || list->infile)
		{
			if (list->arg[0])
			{
				i = 0;
				while(list->arg[i])
					i++;
			}
			// if (list->infile)
			// {
			// 	if (list->infile < 0)
			// 	{
			// 		perror("INFILE");
			// 		exit(EXIT_SUCCESS);
			// 	}
			// 	dup2(list->infile, 0);
			// }
			// if (list->outfile)
			// {
			// 	if (list->outfile < 0)
			// 	{
			// 		perror("OUTFILE");
			// 		exit(EXIT_SUCCESS);
			// 	}
			// 	dup2(list->outfile, 1);
			// }
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
					//printf("%s\n", list->arg[j - 2]);
					j++;
				}
				//j++;
				cmd_args[j] = NULL;
			}
			else if (!list->opt && list->arg)
			{
				cmd = get_cmd2(cmd_path, list->ft);
				cmd_args = malloc(sizeof(char *) * (2 + i));
				cmd_args[0] = list->ft;
				printf("%s\n",cmd_args[0]);
				j = 1;
				printf("%d\n", i);
				while (j < i + 1)
				{
					cmd_args[j] = list->arg[j - 1];
					printf("%s\n", list->arg[j - 1]);
					j++;
				}
				j++;
				cmd_args[j] = NULL;
			}
			else if (!list->opt && !list->arg)
			{
				cmd = get_cmd2(cmd_path, list->ft);
				cmd_args = malloc(sizeof(char *) * 3);
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
		}
	}
	else if (pid)
	{
		waitpid(pid, NULL, 0);
	}
}

 void	ft_exec_simple_pipe(t_list *list, char **cmd_path, char **envp)
{
	int	pid1;
	int	pid2;

	if (pipe(list->piped) < 0)
		return ;
	pid1 = fork();
	if (!pid1)
	{
		if (list->infile)
			dup2(list->infile, 0);
		dup2(list->piped[1], 1);
		close(list->piped[0]);
		ft_exec(list, cmd_path, envp);
	}
	else
		waitpid(pid1, NULL, 0);
	list = list->next;
	pid2 = fork();
	if (!pid2)
	{
		if (list->outfile)
			dup2(list->outfile, 1);
		dup2(list->piped[0], 0);
		close(list->piped[1]);
		ft_exec(list, cmd_path, envp);
	}
	else
		waitpid(pid2, NULL, 0);

}

void	ft_start_exec(t_list *list, char *path, char **envp)
{
	char **cmd_path;
	int	count;

	count = ft_count_forks(list);
	cmd_path = ft_split(path, ':');
	if (count == 1)
	{
		ft_exec(list, cmd_path, envp);
	}
	else if (count == 2)
	{
		ft_exec_simple_pipe(list, cmd_path, envp);
	}
}