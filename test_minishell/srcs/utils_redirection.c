/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:24:05 by lide              #+#    #+#             */
/*   Updated: 2022/09/02 16:50:29 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_copy(char *name, char *str, int *i)
{
	int	j;

	j = -1;
	while (str[++j])
		name[(*i)++] = str[j];
}

char	*find_name(t_list **cmd)
{
	char	*name;
	char	*nb;
	int		len;
	int		i;

	i = 0;
	nb = ft_itoa((*cmd)->pos);
	if (!nb)
		return (NULL);
	len = len1(nb);
	name = (char *)malloc(sizeof(char) * (len + 9));
	if (!name)
	{
		free(nb);
		return (NULL);
	}
	ft_copy(name, ".tmp", &i);
	ft_copy(name, nb, &i);
	ft_copy(name, ".txt", &i);
	name[i] = '\0';
	free(nb);
	return (name);
}

int	cmp_line(char *str, char *line)
{
	int	i;

	if (!str || !line)
		return (0);
	i = 0;
	while (str[i] && line[i] && str[i] == line[i])
		i++;
	if ((!str[i] && line[i]) || (str[i] && !line[i]) || str[i] != line[i])
		return (0);
	return (1);
}

int	remove_red_quote(char **str, int i)
{
	int	verif;

	if (str[i + 1])
	{
		verif = remove_quote(str, (i + 1));
		if (!verif)
			return (0);
	}
	return (1);
}
