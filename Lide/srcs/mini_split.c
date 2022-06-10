/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:20:19 by lide              #+#    #+#             */
/*   Updated: 2022/06/10 20:11:27 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int skip_space(char *line, int *i)
{
	while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' '))
		(*i)++;
	return ((*i));
}

int	skip_and(char *line, int i)
{
	if (line[i] && line[i] == '&')
	{
		while (line[i] && line[i] == '&')
			i++;
	}
	else if (line[i] && line[i] == '|')
	{
		while (line[i] && line[i] == '|')
			i++;
	}
	return (i);
}

char	**split_line(char **str, char *line, int ct)
{
	int	i;
	int	tmp;
	int	len;
	int	loop;

	i = 0;
	loop = -1;
	while (++loop < ct)
	{
		tmp = skip_space(line, &i);
		if (line[i] && !(line[i] == '&' || line[i] == '|'))
			skip_word(line, &i);
		else if (line[i] && (line[i] == '&' || line[i] == '|'))
			i = skip_and(line, i);
		len = i - tmp;
		str[loop] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str[loop])
			return (free_split(str, loop));
		len = 0;
		while (tmp < i)
			str[loop][len++] = line[tmp++];
		str[loop][tmp] = 0;
	}
	return (str);
}

char	**mini_split(char *line)
{
	int		ct;
	char	**str;

	ct = nb_word(line);
	if (ct == -1)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ct + 1));
	if (!str)
		return (NULL);
	str[ct] = NULL;
	str = split_line(str, line, ct);
	if (!str)
		return (NULL);
	return (str);
}
