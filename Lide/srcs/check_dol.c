/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:51:37 by lide              #+#    #+#             */
/*   Updated: 2022/06/15 16:38:54 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*find_env(char *str, int *len, int tmp, int *j)
{
	char	*env;
	char	*line;
	int		i;

	*len = (*j) - tmp;
	line = (char *)malloc(sizeof(char) * ((*len) + 1));
	if (!line)
	{
		free(str);
		*len = -1;
		return (NULL);
	}
	line[*len] = '\0';
	i = -1;
	while (++i < *len)
		line[i] = str[tmp + i];
	env = getenv(line);
	free(line);
	*len = len1(str) + len1(env) - ((*len) + 1);
	return (env);
}

char	*change_env(char *str, int *j, int tmp)
{
	char	*env;
	char	*line;
	int		len;
	int		i;
	int		ct;

	env = find_env(str, &len, tmp, j);
	if (!env && len == -1)
		return (NULL);
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (free_env(str, NULL));
	line[len] = '\0';
	len = len1(env);
	i = -1;
	ct = -1;
	while (++i < tmp - 1)
		line[i] = str[i];
	while (env && env[++ct])
		line[i++] = env[ct];
	ct = i;
	while (str[*j])
		line[i++] = str[(*j)++];
	*j = ct;
	return (free_env(str, line));
}

int	skip_s_quote(char **str, int i, int j)
{
	int	tmp;

	tmp = ++j;
	while (str[i][tmp] && str[i][tmp] != '\'')
		tmp++;
	if (str[i][tmp])
		j = ++tmp;
	return (j);
}

int	find_dol(char **str, int i, int j)
{
	int	tmp;

	tmp = ++(j);
	while (str[i][j] && check_expt(str[i][j], 4))
		(j)++;
	str[i] = change_env(str[i], &j, tmp);
	return (j);
}

char	**check_env(char **str)
{
	int	i;
	int	j;
	int	len;

	len = len2(str);
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'')
				j = skip_s_quote(str, i, j);
			else if (str[i][j] == '$')
			{
				j = find_dol(str, i, j);
				if (!str[i])
					return (free_split(str, len));
			}
			else
				j++;
		}
	}
	return (str);
}
