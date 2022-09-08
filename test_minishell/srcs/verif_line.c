/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:30:25 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/08 19:47:32 by lide             ###   ########.fr       */
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
		write(1, "exit\n", 5);
		free_envp();
		free(line);
		free(cmd);
		rl_clear_history();
		exit (0);
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
	size_t	len;

	while (1)
	{
		len = strlen(line) - 1;
		while (len >= 0)
		{
			while (len >= 0 && ((line[len] >= 9 && line[len] <= 13)
					|| line[len] == ' '))
				len--;
			if (len >= 0 && line[len] == '|')
			{
				line = ft_readline(line, cmd);
				if (!line)
					return (NULL);
				return (verif_line(line, cmd));
			}
			else
				return (line);
		}
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
