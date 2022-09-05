/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_dol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:40:07 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 21:41:29 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_line(char *line)
{
	int	len;
	int	i;

	len = len1(line);
	i = 0;
	if (len == 1 && !((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		return (0);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			return (1);
		else if ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
			return (1);
	}
	return (0);
}

int	check_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
			return (0);
	}
	return (1);
}

char	**put_empty(char **str, char *line, int *i)
{
	char	*empty;

	empty = malloc(sizeof(char));
	if (!empty)
	{
		free(line);
		str[*i] = NULL;
		return (str);
	}
	empty[0] = '\0';
	str[*i] = empty;
	return (str);
}

char	**realloc_str2(char **str, char **split, int *i, int x)
{
	int		len;
	int		len_sp;
	char	**new;

	len = len2(str);
	len_sp = len2(split);
	new = malloc(sizeof(char *) * (len + len_sp));
	if (!new)
	{
		str[*i] = free_split(split, len2(split));
		return (str);
	}
	x = -1;
	while (++x < *i)
		new[x] = str[x];
	len = -1;
	while (split[++len])
	new[x++] = split[len];
	len = x - 1;
	while (str[++(*i)])
		new[x++] = str[*i];
	new[x] = NULL;
	*i = len;
	return (new);
}

char	**realloc_str(char **str, char **line, int *i)
{
	int		x;
	char	**split;

	x = 0;
	if (check_line(*line))
	{
		if (check_empty(*line))
			return (put_empty(str, *line, i));
		split = mini_split(*line);
		if (!split)
		{
			str[*i] = NULL;
			return (str);
		}
		return (realloc_str2(str, split, i, x));
	}
	else
	{
		str[*i] = *line;
		return (str);
	}
}
