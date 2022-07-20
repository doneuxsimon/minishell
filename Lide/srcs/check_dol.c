/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:51:37 by lide              #+#    #+#             */
/*   Updated: 2022/07/20 18:40:01 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*find_env(char *str, int *len, int tmp, int *j)
{
	char	*env;
	char	*line;

	line = cp_name(str, len, tmp, j);
	if (!line)
		return (NULL);
	env = getenv(line);
	if (!env)
	{
		if (check_g_var(line))
		{
			env = cp_value(g_var->value, line, len);
			if (!env)
				return (NULL);
		}
	}
	else
	{
		env = cp_value(env, line, len);
		if (!env)
			return (NULL);
	}
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
		return (free_char(env));
	line[len] = '\0';
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
	return (free_env(str, line, env));
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

char	**check_dol(char **str)
{
	int	i;
	int	j;
	int	len;
	int	verif;

	i = -1;
	verif = 1;
	len = len2(str);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '\"')
				verif *= -1;
			if (str[i][j] == '\'' && verif > 0)
				j = (skip_s_quote(str, i, j) - 1);
			else if (str[i][j] == '$')
				j = (find_dol(str, i, j) - 1);
			if (!str[i])
				return (free_split(str, len));
		}
	}
	return (str);
}
