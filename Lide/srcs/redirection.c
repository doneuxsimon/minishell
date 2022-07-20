/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:12:08 by lide              #+#    #+#             */
/*   Updated: 2022/07/20 18:46:52 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	next_struct(t_list **cmd, int *i, char **str)
{
	t_list	*new;

	new = NULL;
	(*cmd)->link = str[*i];
	(*i)++;
	new = init_lst(new);
	if (!new)
		return (0);
	new->pos = ((*cmd)->pos) + 1;
	new->before = *cmd;
	(*cmd)->next = new;
	*cmd = (*cmd)->next;
	return (1);
}

void	free_find_outfile(char **str, int *i, int fd)
{
	free(str[*i]);
	str[(*i)++] = NULL;
	if (fd != -1)
	{
		free(str[*i]);
		str[*i] = NULL;
	}
}

int	find_outfile(char **str, t_list **cmd, int *i)
{
	int	fd;

	if (!remove_red_quote(str, *i))
		return (0);
	if ((*cmd)->outfile != 0)
		close((*cmd)->outfile);
	if (!str[*i + 1] || (str[*i + 1] && str[*i + 1][0] == '<'))
		fd = -1;
	else if (str[*i][1] && str[*i][1] == '>')
		fd = open(str[*i + 1], O_CREAT | O_RDWR | O_APPEND, 00644);
	else
	{
		fd = open(str[*i + 1], O_CREAT | O_RDWR | O_TRUNC, 00644);
		if (fd != -1)
		{
			close(fd);
			fd = open(str[*i + 1], O_CREAT | O_RDWR | O_APPEND, 00644);
		}
	}
	free_find_outfile(str, i, fd);
	(*cmd)->outfile = fd;
	return (1);
}

int	redirection(char **str, t_list **cmd, int len)
{
	int	i;
	int	verif;

	i = 0;
	verif = 1;
	while (i < len)
	{
		if (str[i])
		{
			if (str[i][0] == '>')
				verif = find_outfile(str, cmd, &i);
			else if (str[i][0] == '<')
				verif = find_infile(str, cmd, &i);
			else if (str[i][0] == '&' || str[i][0] == '|')
				verif = next_struct(cmd, &i, str);
			else
				i++;
			if ((*cmd)->outfile == -1 || (*cmd)->infile == -1 || !verif)
				free_redirection(str, cmd, len);
		}
		else
			i++;
	}
	return (1);
}
