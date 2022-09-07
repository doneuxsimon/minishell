/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:30:25 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/07 18:50:01 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*ft_readline(char *line, t_list *cmd)
{
	char	*tmp;

	tmp = readline("> ");
	if (!tmp)
	{
		write(1, "exit\n", 5);
		free_envp();
		free(cmd);
		rl_clear_history();
		exit (0);
	}
	line = ft_strjoin_2(line, tmp);
	if (!line)
	{
		perror("Strjoin");
		write(1, "exit\n", 5);//dans l'idee
		free_envp();
		free(cmd);
		rl_clear_history();
		exit (0);
		// return (NULL);
	}
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
