/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:42:40 by lide              #+#    #+#             */
/*   Updated: 2022/07/28 17:25:25 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	write_in_file(int fd, char **str, t_list **cmd, int *i)
{
	char	*line;

	sig(2);
	if (g_var->error == 1)
	{
		return (0);
	}
	while (1)
	{
		if (g_var->error != 1)
			line = readline("> ");
		if (g_var->error == 1)
		{
			break;
		}
		if (!line)
		{
			printf(error2 error2bis"\n", (*cmd)->ct_line, str[*i + 1]);
			break ;
		}
		// if (cmp_line("^C", line))//doit suprimer le fichier tmp
		// 	return (0); doit trouver soluce pour ctrl c
		if (cmp_line(str[*i + 1], line))
			break ;
		write (fd, line, len1(line));
		write (fd, "\n", 1);
		free(line);
		printf("%d\n", g_var->error);
	}
	free(line);
	if (g_var->error == 1)
	{
		return (0);
	}
	return (1);
}

int	create_tmp_file(char **str, t_list **cmd, int *i)
{
	char	*name;
	int		fd;
	int		verif;

	name = find_name(cmd);
	if (!name)
		return (0);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		return (0);
	verif = write_in_file(fd, str, cmd, i);
	close(fd);
	if (fd == -1 || verif == 0)
		return (0);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (0);
	(*cmd)->infile = fd;
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
		if (close((*cmd)->infile) == -1)//check si tout ok
			return (0);
	if (!str[*i + 1] || (str[*i + 1] && str[*i + 1][0] == '>'))
		return (print_error(error1));
	else if (str[*i][1] && str[*i][1] == '<')
	{
		if (!create_tmp_file(str, cmd, i))
		{
			if (g_var->error != 1)
				return (print_perror("infile"));
			else
				return (0);
		}
	}
	else
		fd = open(str[*i + 1], O_RDONLY);
	if (fd == -1)
		return (print_perror("infile"));
	free(str[*i]);
	str[(*i)++] = NULL;
	free(str[*i]);
	str[*i] = NULL;
	return (1);
}
