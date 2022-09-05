/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:36:37 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 21:45:34 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_g_var(char *str)
{
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		if (cmp_line(str, g_var->name))
			return (1);
		g_var = g_var->next;
	}
	if (cmp_line(str, g_var->name))
		return (1);
	return (0);
}

int	put_g_name(char *tmp, int verif)
{
	t_var	*new;

	new = NULL;
	if (verif == 0)
	{
		g_var->name = tmp;
		new = init_var(new);
		if (!new)
			return (0);
		new->returned = g_var->returned;
		new->pid = g_var->pid;
		new->before = g_var;
		g_var->next = new;
		g_var = g_var->next;
	}
	else
		free(tmp);
	return (1);
}

int	put_g_value(char *str, char *tmp, int *verif, int j)
{
	int		x;
	int		ct;
	int		len;
	char	*new;

	x = 0;
	ct = j;
	len = len1(str);
	new = (char *)malloc(sizeof(char) * (len - (j - 1)));
	if (!new)
		return (0);
	*verif = check_g_var(tmp);
	if (*verif)
		free(g_var->value);
	while (++ct < len)
		new[x++] = str[ct];
	new[x] = '\0';
	g_var->value = new;
	return (1);
}

int	put_in_g(char **str, int i, int j)
{
	int		ct;
	int		x;
	int		verif;
	char	*tmp;

	x = 0;
	ct = -1;
	tmp = (char *)malloc(sizeof(char) * (j));
	if (!tmp)
		return (0);
	while (++ct < j)
		tmp[x++] = str[i][ct];
	tmp[ct] = '\0';
	x = put_g_value(str[i], tmp, &verif, j);
	if (!x)
	{
		free(tmp);
		return (0);
	}
	return (put_g_name(tmp, verif));
}

int	ft_export(char **str, int i, int len)
{
	int	j;
	int	verif;

	while (i < len)
	{
		if (str[i])
		{
			if (str[i][0] == '|' || str[i][0] == '&')
				break ;
			j = 0;
			while (str[i][j] && str[i][j] != '=')
				j++;
			j = check_w_sp(str[i], j);
			if (j > -1 && str[i][j])
			{
				verif = put_in_g(str, i, j);
				if (!verif)
					return ((print_perror("export") + 1));
			}
		}
		i++;
	}
	return (0);
}
