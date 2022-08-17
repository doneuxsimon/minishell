/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:20:21 by lide              #+#    #+#             */
/*   Updated: 2022/08/17 18:53:54 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_expt(char c, int verif)
{
	if (verif == 0)
		if (c == '&' || c == '|' || c == '<' || c == '>')
			return (0);
	if (verif == 1 || verif == 2 || verif == 4)
		if (c == '&' || c == '|' || (c >= 9 && c <= 13) || c == 32
			|| c == '<' || c == '>')
			return (0);
	if (verif == 2 || verif == 3 || verif == 4)
		if (c == '\'' || c == '\"')
			return (0);
	if (verif == 4)
		if (c == '$')
			return (0);
	return (1);
}

int	skip_word(char *line, int i)
{
	int		tmp;
	char	quote;

	while (line[i] && check_expt(line[i], 1))
	{
		while (line[i] && check_expt(line[i], 2))
			i++;
		if (line[i] && !check_expt(line[i], 3))
		{
			quote = line[i];
			i++;
			tmp = i;
			while (line[tmp] && line[tmp] != quote)
				tmp++;
			if (line[tmp])
				i = ++tmp;
			else
			{
				printf("quote not closed\n");
				return (-1);
			}
		}
	}
	return (i);
}

int	skip_sep(char *line, int i, char sep)
{
	int	ct;

	ct = 0;
	while (line[i] && line[i] == sep)
	{
		if (++ct > 2)
		{
			while (line[i] && line[i] == sep)
			{
				i++;
				ct++;
			}
			skip_sep_error(ct - 1, sep);
			return (-1);
		}
		i++;
	}
	return (i);
}

int	skip_separator(char *line, int i)
{
	if (line[i] == '&')
		i = skip_sep(line, i, '&');
	else if (line[i] == '|')
		i = skip_sep(line, i, '|');
	else if (line[i] == '>')
		i = skip_sep(line, i, '>');
	else if (line[i] == '<')
		i = skip_sep(line, i, '<');
	return (i);
}

int	skip_space(char *line, int *i)
{
	while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' '))
		(*i)++;
	return ((*i));
}
