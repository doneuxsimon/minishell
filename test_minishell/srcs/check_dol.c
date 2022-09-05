/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:51:37 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 16:08:58 by lide             ###   ########.fr       */
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

char	**realloc_str(char **str, char *line, int *i)
{
	int		x;
	int		len;
	int		len_sp;
	char	**split;
	char	**new;

	if (check_line(line))
	{
		if (check_empty(line))
			return (put_empty(str, line, i));
		split = mini_split(line);
		if (split)
		{
			free(line);
			str[*i] = NULL;
			return (str);
		}
		len = len2(str);
		len_sp = len2(split);
		new = malloc(sizeof(char *) * (len + len_sp));//potentiel leaks
		if (new)
		{
			free(line);
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
	else
	{
		str[*i] = line;
		return (str);
	}
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
	(*str) = realloc_str((*str), line, i);
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
