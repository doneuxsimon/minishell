/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:51:37 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 21:41:35 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*find_env(char *str, int *len, int tmp, int *j)
{
	char	*env;
	char	*line;

	env = NULL;
	line = cp_name(str, len, tmp, j);
	if (!line)
		return (NULL);
	if (check_g_var(line))
	{
		env = cp_value(g_var->value, line, len);
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
		return (print_str_perror("var env"));
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (free_char(env, "var env"));
	line[len] = '\0';
	i = -1;
	ct = -1;
	while (++i < tmp - 1)
		line[i] = str[i];
	while (env && env[++ct])
		line[i++] = env[ct];
	ct = i - 1;
	while (str[*j])
		line[i++] = str[(*j)++];
	*j = ct;
	return (free_env(str, line, env));
}

int	find_dol(char ***str, int *i, int j)
{
	int		max;
	int		diff;
	int		tmp;
	char	*line;

	tmp = ++(j);
	while ((*str)[*i][j] && check_expt((*str)[*i][j], 4))
		(j)++;
	max = j;
	diff = 0;
	while ((*str)[*i][max++])
		diff++;
	line = change_env((*str)[*i], &j, tmp);
	(*str) = realloc_str((*str), &line, i);
	max = len1((*str)[*i]);
	j = max - diff;
	return (j);
}

int	change_question(char **str, int i, int j)
{
	int		x;
	int		z;
	char	*line;
	char	*nb;

	x = -1;
	z = -1;
	nb = ft_itoa(*g_var->returned);
	if (!nb)
		return (change_question_error(str, nb, i, 0));
	line = (char *)malloc(sizeof(char) * (len1(str[i]) + 1));
	if (!line)
		return (change_question_error(str, nb, i, 1));
	while (++x < j)
		line[x] = str[i][x];
	while (nb[++z])
		line[x++] = nb[z];
	z = x - 1;
	j += 1;
	while (str[i][++j])
		line[x++] = str[i][j];
	line[x] = '\0';
	str[i] = line;
	return (z);
}

char	**check_dol(char **str, int len)
{
	int	i;
	int	j;
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
			else if (str[i][j] == '$' && str[i][j + 1] && str[i][j + 1] == '?')
				j = change_question(str, i, j);
			else if (str[i][j] == '$' && str[i][j + 1])
				j = (find_dol(&str, &i, j) - 1);
			if (!str[i])
				return (free_split(str, len));
		}
	}
	return (str);
}
