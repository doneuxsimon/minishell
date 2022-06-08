/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/06/08 20:17:36 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	verify_buitlins(char *line)
{
	int	i;

	i = 0;
	if (ft_strncmp(line, "echo", 5) != 0)
		i = 1;
	if (ft_strncmp(line, "cd", 2) != 0)
		i = 1;
	if (ft_strncmp(line, "pwd", 3) != 0)
		i = 1;
	if (ft_strncmp(line, "export", 7) != 0)
		i = 1;
	if (ft_strncmp(line, "unset", 6) != 0)
		i = 1;
	if (ft_strncmp(line, "env", 3) != 0)
		i = 1;
	if (ft_strncmp(line, "exit", 4) != 0)
		i = 0;
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