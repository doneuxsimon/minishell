/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:30:25 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/12 18:01:26 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*ft_readline(char *line, t_list *cmd)
{
	char	*tmp;
	char	*str;

	tmp = readline("> ");
	if (!tmp)
	{
		printf("minishell: syntax error: unexpected end of file\nexit\n");
		free_envp();
		free(line);
		free(cmd);
		rl_clear_history();
		exit (2);
	}
	str = ft_strjoin_2(line, tmp);
	if (!str)
	{
		perror("Strjoin");
		free(tmp);
		add_history(line);
		return (NULL);
	}
	free(line);
	line = str;
	free(tmp);
	return (line);
}

char	*verif_line(char *line, t_list *cmd)
{
	int	len;

	while (1)
	{
		len = len1(line) - 1;
		while (len >= 0)
		{
			while (len >= 0 && ((line[len] >= 9 && line[len] <= 13)
					|| line[len] == ' '))
				len--;
			if (len >= 1 && line[len] == '|' && line[len - 1] != '|')
			{
				line = ft_readline(line, cmd);
				if (!line)
					return (NULL);
				return (verif_line(line, cmd));
			}
			else
				return (line);
		}
		return (line);
	}
}

void	ft_exit_utils(t_list *cmd)
{
	int	tmp;

	printf("exit\n");
	tmp = ft_atoi(cmd->arg[0]);
	if (!tmp)
		tmp = 1;
	free_all(&cmd, 0);
	exit(tmp);
}
