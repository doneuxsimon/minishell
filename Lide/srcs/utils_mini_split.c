/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:20:21 by lide              #+#    #+#             */
/*   Updated: 2022/06/10 19:55:55 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	*free_split(char **str, int max)
{
	int	i;

	i = -1;
	while (++i < max)
		free(str[i]);
	free(str);
	return (NULL);
}

int	check_expt(char c, int verif)
{
	if (verif == 1 || verif == 2)
	{
		if (c == '&' || c == '|' || (c >= 9 && c <= 13) || c == 32)
			return (0);
	}
	if (verif == 2 || verif == 3)
	{
		if (c == '\'' || c == '\"')
			return (0);
	}
	return (1);
}

void	skip_word(char *line, int *i)
{
	int		tmp;
	char	quote;

	while (line[*i] && check_expt(line[*i], 1))
	{
		while (line[*i] && check_expt(line[*i], 2))
			(*i)++;
		if (line[*i] && !check_expt(line[*i], 3))
		{
			quote = line[*i];
			(*i)++;
			tmp = *i;
			while (line[tmp] && line[tmp] != quote)
				tmp++;
			if (line[tmp])
			{
				tmp++;
				(*i) = tmp;
			}
		}
	}
}

int skip_or(char *line, int i, char sep)
{
	int	ct;

	ct = 0;
	while (line[i] && line[i] == sep)
	{
		i++;
		if (++ct > 2)
			return (-1);
	}
	return (i);
}

int	nb_word(char *line)
{
	int	i;
	int	word;
	int	ct;

	i = 0;
	word = 0;
	while (line[i])
	{
		ct = 0;
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
			i++;
		skip_word(line, &i);
		// if (line[i] && (line[i] == '&' || line[i] == '|'))
		// 	word++;
		if (line[i] && line[i] == '&')
			i = skip_or(line, i, '&');
		else if (line[i] && line[i] == '|')
			i = skip_or(line, i, '|');
		if (i == -1)
			return (i);
		// while (line[i] && (line[i] == '&' || line[i] == '|'))//doit differencier le deux si triple
		// {
		// 	i++;
		// 	if (++ct > 2)
		// 		return (-1);
		// }
		word++;
	}
	printf("%d\n", word);
	return (word);
}
