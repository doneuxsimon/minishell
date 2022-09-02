/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_dol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:37:40 by lide              #+#    #+#             */
/*   Updated: 2022/09/02 21:25:19 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

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

char	*cp_name(char *str, int *len, int tmp, int *j)
{
	char	*line;
	int		i;

	*len = (*j) - tmp;
	line = (char *)malloc(sizeof(char) * ((*len) + 1));
	if (!line)
	{
		*len = -1;
		return (NULL);
	}
	line[*len] = '\0';
	i = -1;
	while (++i < *len)
		line[i] = str[tmp + i];
	return (line);
}

char	*cp_value(char *value, char *line, int *len)
{
	char	*env;

	env = ft_strdup(value);
	if (!env)
	{
		free(line);
		*len = -1;
		return (NULL);
	}
	return (env);
}
