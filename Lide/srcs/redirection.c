/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:12:08 by lide              #+#    #+#             */
/*   Updated: 2022/07/14 17:22:30 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	find_outfile(char **str, t_list **cmd, int *i)//proteger quote
{
	int	fd;

	if (str[*i + 1])
		remove_quote(str, (*i + 1));
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
	str[(*i)++] = NULL;
	if (fd != -1)
		str[*i] = NULL;
	(*cmd)->outfile = fd;
}

void	write_in_file(int fd, char **str, int *i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("error ctrl d while <<\n");
			break ;
		}
		if (cmp_line(str[*i + 1], line))
			break ;
		write (fd, line, len1(line));
		write (fd, "\n", 1);
		free(line);
	}
	free(line);
}

void	find_infile(char **str, t_list **cmd, int *i)//proteger quote
{
	int		fd;
	char	*name;

	if (str[*i + 1])
		remove_quote(str, (*i + 1));
	if ((*cmd)->infile != 0)
		close((*cmd)->infile);
	if (!str[*i + 1] || (str[*i + 1] && str[*i + 1][0] == '>'))
		fd = -1;
	else if (str[*i][1] && str[*i][1] == '<')
	{
		name = find_name(cmd);
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 00644);
		write_in_file(fd, str, i);
		close(fd);
		(*cmd)->infile = open(name, O_RDONLY);
		(*cmd)->tmp = name;
	}
	else
		fd = open(str[*i + 1], O_RDONLY);
	str[(*i)++] = NULL;
	if (fd != -1)
		str[*i] = NULL;
	(*cmd)->infile = fd;
}

void	next_struct(t_list **cmd, int *i, char **str)
{
	t_list		*new;
	// static int	pos;

	new = NULL;
	(*cmd)->link = str[*i];
	(*i)++;
	new = init_lst(new);
	new->pos = ((*cmd)->pos) + 1;
	new->before = *cmd;
	(*cmd)->next = new;
	*cmd = (*cmd)->next;
}

void	redirection(char **str, t_list **cmd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i])
		{
			if (str[i][0] == '>')
				find_outfile(str, cmd, &i);
			else if (str[i][0] == '<')
				find_infile(str, cmd, &i);
			else if (str[i][0] == '&' || str[i][0] == '|')
			{
				printf("%d\n", (*cmd)->pos);
				next_struct(cmd, &i, str);
				printf("%d\n", (*cmd)->pos);
			}
			else
				i++;
			if ((*cmd)->outfile == -1 || (*cmd)->infile == -1)
			{
				printf("error\n");
				exit(0);
			}
		}
		else
			i++;
	}
}
