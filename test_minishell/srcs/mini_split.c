/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:20:19 by lide              #+#    #+#             */
/*   Updated: 2022/08/18 19:15:52 by lide             ###   ########.fr       */
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
		if (line[i] && check_expt(line[i], 0))
			i = skip_word(line, i);
		else if (line[i] && !check_expt(line[i], 0))
			i = skip_separator(line, i);
		len = i - tmp;
		str[loop] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str[loop])
			return (free_split(str, loop));
		str[loop][len] = '\0';
		len = 0;
		while (tmp < i)
			str[loop][len++] = line[tmp++];
	}
	return (str);
}

int	nb_word(char *line)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (line[i])
	{
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
			i++;
		if (line[i] && check_expt(line[i], 0))
		{
			i = skip_word(line, i);
			if (i == -1)
				return (-1);
			word++;
		}
		if (line[i] && !check_expt(line[i], 0))
		{
			i = skip_separator(line, i);
			word++;
		}
		if (i == -1)
			return (-1);
	}
	return (word);
}

char	**mini_split(char *line)
{
	int		ct;
	char	**str;

	ct = nb_word(line);
	if (ct == -1)
	{
		free(line);
		return (NULL);
	}
	str = (char **)malloc(sizeof(char *) * (ct + 1));
	if (!str)
	{
		free(line);
		return ((char **)print_str_perror("mini_split"));
	}
	str[ct] = NULL;
	str = split_line(str, line, ct);
	if (!str)
	{
		perror("mini_split");
		free(line);
		return (NULL);
	}
	free(line);
	return (str);
}
