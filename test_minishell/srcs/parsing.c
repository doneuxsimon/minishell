/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/16 18:00:27 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"


void	ft_env()
{
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		printf("%s| value = %s\n", g_var->name, g_var->value);
		g_var = g_var->next;
	}
	//printf("%s| value = %s\n", g_var->name, g_var->value);
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	ft_echo(t_list *list)
{
	int i;
	
	i = 0;
	while(list->arg[i])
	{
		printf("%s", list->arg[i]);
		if (list->arg[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_cd(t_list *list)
{
	chdir(list->arg[0]);
}

void	ft_pwd(void)
{
	char *tmp;

	tmp = getcwd(NULL,  0);
	printf("%s\n", tmp);
	free(tmp);
}

void ft_minishell(char **envp)
{
	int pid;
	char **cmd_args;

	printf("jeff\n");
	cmd_args = malloc(sizeof(char *) * 2);
	cmd_args[0] = malloc(sizeof(char) * 9);
	cmd_args[0] = "minishell";
	cmd_args[1] = NULL;
	pid = fork();
	if (!pid)
	{
		execve(get_cmd2(envp, "open"), cmd_args, envp);
	}
	if (pid)
		waitpid(pid, NULL, 0);
}

int	verify_builtins(t_list *list, char **envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(list->ft, "echo", 3) == 0)
	{
		ft_echo(list);
		i = 1;
	}
	if (ft_strncmp(list->ft, "cd", 3) == 0)
	{
		dprintf(2, "jefff\n");
		ft_cd(list);
		i = 1;
	}
	if (ft_strncmp(list->ft, "pwd", 3) == 0)
	{
		ft_pwd();
		i = 1;
	}
	if (ft_strncmp(list->ft, "env", 3) == 0)
	{
		ft_env();
		i = 1;
	}
	if (ft_strncmp(list->ft, "exit", 4) == 0)
	{
		ft_exit();
		i = 1;
	}
	if (ft_strncmp(list->ft, "./minishell", 11) == 0)
	{
		ft_minishell(envp);
		i = 1;
	}
	return (i);
}

char	*get_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*command;
	char	**cmd_paths;

	cmd_paths = ft_split(path, ':');
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
