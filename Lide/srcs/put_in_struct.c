/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/06/20 17:31:38 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	find_outfile(char **tmp, t_list *cmd, int *i)
{
	int	fd;

	if (cmd->outfile != 0)
		close(cmd->outfile);
	if (!tmp[*i + 1] || (tmp[*i + 1] && tmp[*i + 1][1] == '<'))
		fd = -1;
	else if (tmp[*i][1] && tmp[*i][1] == '>')
		fd = open(tmp[*i + 1], O_CREAT | O_RDWR | O_APPEND, 00644);
	else
	{
		fd = open(tmp[*i + 1], O_CREAT | O_RDWR | O_TRUNC, 00644);
		if (fd != -1)
		{
			close(fd);
			fd = open(tmp[*i + 1], O_CREAT | O_RDWR | O_APPEND, 00644);
		}
	}
	tmp[*i++] = NULL;
	if (fd != -1)
		tmp[*i] = NULL;
	cmd->outfile = fd;
}

int	cmp_line(char *tmp, char *line)
{
	int	i;

	i = 0;
	while (tmp[i] && line[i] && tmp[i] == line[i])
		i++;
	if ((!tmp[i] && line[i]) || (tmp[i] && !line[i]) || tmp[i] != line[i])
		return (0);
	return (1);
}

void	write_in_file(int fd, char **tmp, int *i)
{
	char *line;
	while (1)
	{
		line = readline("> ");
		if (cmp_line(tmp[*i + 1], line))
			break ;
		write (fd, line, len1(line));
		free(line);
	}
	free(line);
}

void ft_copy(char *name, char *str, int *i)
{
	int j;

	j = -1;
	while (str[++j])
		name[(*i)++] = str[j];
}

char *find_name(t_list *cmd)
{
	char	*name;
	char	*nb;
	int		len;
	int		i;

	i = 0;
	nb = ft_itoa(cmd->pos);
	if (!nb)
		exit (0);
	len = len1(nb);
	name = (char *)malloc(sizeof(char) * (len + 9));
	ft_copy(name, ".tmp", &i);
	ft_copy(name, nb, &i);
	ft_copy(name, ".txt", &i);
	name[i] = '\0';
	return (name);
}

void	find_infile(char **tmp, t_list *cmd, int *i)
{
	int	fd;
	char *name;

	if (cmd->infile != 0)
		close(cmd->infile);
	if (!tmp[*i + 1] || (tmp[*i + 1] && tmp[*i + 1][1] == '>'))
		fd = -1;
	else if (tmp[*i][1] && tmp[*i][1] == '<')
	{
		name = find_name(cmd);
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 00644);
		write_in_file(fd, tmp, i);
		close(fd);
		cmd->infile = open(name, O_RDONLY);
		cmd->tmp = name;
	}
	else
		fd = open(tmp[*i + 1], O_RDONLY);
	tmp[*i++] = NULL;
	if (fd != -1)
		tmp[*i] = NULL;
	cmd->infile = fd;
}

void	next_struct(t_list *cmd, int *i, char **tmp)
{
	t_list	*new;
	static int pos;

	new = NULL;
	cmd->link = tmp[*i];
	(*i)++;
	new = init_lst(new);
	new->pos = ++pos;
	cmd->next = new;
	cmd = cmd->next;
}

void	redirection(char **tmp,t_list *cmd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tmp[i])
		{
			if (tmp[i][0] == '>')
				find_outfile(tmp, cmd, &i);
			else if (tmp[i][0] == '<')
				find_infile(tmp, cmd, &i);
			else if (tmp[i][0] == '&' || tmp[i][0] == '|')
				next_struct(cmd, &i, tmp);
			else
				i++;
			if (cmd->outfile == -1 || cmd->infile == -1)
			{
				printf("error\n");
				exit(0);
			}
		}
		else
			i++;
	}
}

void	put_in_struct(char **str,t_list *cmd)
{
	char **tmp;
	int len;
	int i;

	i = -1;
	tmp = str;
	len = len2(str);
	redirection(tmp, cmd, len);
	while (++i < len)
		printf("%s\n", tmp[i]);
}
