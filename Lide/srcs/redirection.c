/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:12:08 by lide              #+#    #+#             */
/*   Updated: 2022/07/19 18:14:47 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	find_outfile(char **str, t_list **cmd, int *i)//proteger quote
{
	int	fd;
	int	verif;

	if (str[*i + 1])
	{
		verif = remove_quote(str, (*i + 1));
		if (!verif)
			return (0);
	}
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
	free(str[*i]);
	str[(*i)++] = NULL;
	if (fd != -1)
	{
		free(str[*i]);
		str[*i] = NULL;
	}
	(*cmd)->outfile = fd;
	return (1);
}

void	write_in_file(int fd, char **str, int *i)//doit vraiment free line ?
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

int	find_infile(char **str, t_list **cmd, int *i)//proteger quote
{
	int		fd;
	char	*name;
	int		verif;

	if (str[*i + 1])
	{
		verif = remove_quote(str, (*i + 1));
		if (!verif)
			return (0);
	}
	if ((*cmd)->infile != 0)
		close((*cmd)->infile);
	if (!str[*i + 1] || (str[*i + 1] && str[*i + 1][0] == '>'))
		fd = -1;
	else if (str[*i][1] && str[*i][1] == '<')
	{
		name = find_name(cmd);
		if (!name)
			return (0);
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 00644);
		write_in_file(fd, str, i);
		close(fd);
		(*cmd)->infile = open(name, O_RDONLY);
		(*cmd)->tmp = name;
	}
	else
		fd = open(str[*i + 1], O_RDONLY);
	free(str[*i]);
	str[(*i)++] = NULL;
	if (fd != -1)
	{
		free(str[*i]);
		str[*i] = NULL;
	}
	return (1);
}

int	next_struct(t_list **cmd, int *i, char **str)
{
	t_list		*new;

	new = NULL;
	(*cmd)->link = str[*i];
	(*i)++;
	new = init_lst(new);
	if (!new)
		return(0);
	new->pos = ((*cmd)->pos) + 1;
	new->before = *cmd;
	(*cmd)->next = new;
	*cmd = (*cmd)->next;
	return(1);
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
			{
				//selon l'erreur mettre un msg
				free_envp();
				free_all(cmd);
				free_split(str, len);
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}
