/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_dol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:37:40 by lide              #+#    #+#             */
/*   Updated: 2022/06/17 10:17:45 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*free_env(char *str, char *ret)
{
	free(str);
	return (ret);
}

int	len1(char *str)
{
	int	ct;

	if (!str)
		return (0);
	ct = 0;
	while (str[ct])
		ct++;
	return (ct);
}

int	len2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*unchange_env(char *str, int *j, int len)
{
	int		i;
	int		tmp;
	char	*line;

	if (len == -1)
		return (NULL);
	i = -1;
	tmp = *j + 1;
	len = len1(str);
	line = (char *)malloc(sizeof(char) * (len + 2));
	while (++i < *j)
		line[i] = str[i];
	line[i] = '|';
	while (str[*j])
		line[++i] = str[(*j)++];
	line[++i] = '\0';
	*j = tmp;
	free(str);
	return (line);
}
