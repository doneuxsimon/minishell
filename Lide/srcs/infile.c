/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:42:40 by lide              #+#    #+#             */
/*   Updated: 2022/07/21 18:45:45 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

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

int	create_tmp_file(char **str, t_list **cmd, int *i, int *fd)
{
	char	*name;

	name = find_name(cmd);
	if (!name)
		return (0);
	*fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	write_in_file(*fd, str, i);
	close(*fd);
	(*cmd)->infile = open(name, O_RDONLY);
	(*cmd)->tmp = name;
	return (1);
}

int	find_infile(char **str, t_list **cmd, int *i)
{
	int		fd;

	fd = 0;
	if (!remove_red_quote(str, *i))
		return (0);
	if ((*cmd)->infile != 0)
		close((*cmd)->infile);
	if (!str[*i + 1] || (str[*i + 1] && str[*i + 1][0] == '>'))
		fd = -1;
	else if (str[*i][1] && str[*i][1] == '<')
	{
		if (!create_tmp_file(str, cmd, i, &fd))
			return (0);
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
