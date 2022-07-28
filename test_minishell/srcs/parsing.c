/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/07/28 17:07:37 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	ft_echo(char *line)
{
	char **splitted;

	splitted = ft_split(line, ' ');
	if (!splitted[1])
		printf("\n");
	else
		printf("%s\n", splitted[1]);
}

void	ft_cd(char *line)
{
	char **splitted;

	splitted = ft_split(line, ' ');
	chdir(splitted[1]);
	free(splitted);
}

void	ft_pwd(void)
{
	char *tmp;

	tmp = getcwd(NULL,  0);
	printf("%s\n", tmp);
	free(tmp);
}

// void	ft_unset(char *line)
// {
// 	char **splitted;

// 	splitted = ft_split(line, ' ');
// 	unlink(splitted[1]);
// 	free(splitted);
// }

int	verify_builtins(char *line, char **envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(line, "echo", 4) == 0)
	{
		ft_echo(line);
		i = 1;
	}
	if (ft_strncmp(line, "cd", 1) == 0)
	{
		ft_cd(line);
		i = 1;
	}
	if (ft_strncmp(line, "pwd", 2) == 0)
	{
		ft_pwd();
		i = 1;
	}
	if (ft_strncmp(line, "export", 6) == 0)
		i = 1;
	// if (ft_strncmp(line, "unset", 5) == 0)
	// {
	// 	ft_unset(line);
	// 	i = 1;
	// }
	if (ft_strncmp(line, "env", 2) == 0)
	{
		ft_env(envp);
		i = 1;
	}
	if (ft_strncmp(line, "exit", 3) == 0)
	{
		ft_exit();
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
