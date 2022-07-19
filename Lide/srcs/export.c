/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:36:37 by lide              #+#    #+#             */
/*   Updated: 2022/07/19 18:22:14 by lide             ###   ########.fr       */
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

int	put_in_g(char **str, int i, int j)
{
	int		len;
	int		ct;
	int		x;
	int		t;
	t_var	*new;
	char	*tmp;

	ct = -1;
	len = len1(str[i]);
	new = NULL;
	x = 0;
	tmp = (char *)malloc(sizeof(char) * (j));
	if (!tmp)
	{
		printf("error malloc put in g\n");
		return (0);
	}
	while (++ct < j)
		tmp[x++] = str[i][ct];
	tmp[ct] = '\0';
	t = check_g_var(tmp);
	if (t)
	{
		free(g_var->value);
		free(tmp);
	}
	g_var->value = (char *)malloc(sizeof(char) * (len - (j - 1)));
	if (!g_var->value)
	{
		printf("error malloc put in g\n");
		return (0);
	}
	x = 0;
	while (++ct < len)
		g_var->value[x++] = str[i][ct];
	g_var->value[x] = '\0';
	if (t == 0)
	{
		g_var->name = tmp;
		new = init_var(new);
		if (!new)
			return (0);
		new->before = g_var;
		g_var->next = new;
		g_var = g_var->next;
	}
	return (1);
}

int	ft_export(char **str, int *i, int len)
{
	int	j;
	int	verif;

	(*i)++;
	while (*i < len)
	{
		if (str[*i])
		{
			if (str[*i][0] == '|' || str[*i][0] == '&')
				break ;
			j = 0;
			while (str[*i][j] && str[*i][j] != '=')
				j++;
			if (str[*i][j])
			{
				verif = put_in_g(str, *i, j);
				if (!verif)
					return (0);
			}
		}
		(*i)++;
	}
	return (1);
}

// void	find_esp(int *i, int len, char **str)
// {
// 	int	tmp;

// 	tmp = *i;
// 	while (tmp < len)
// 	{
// 		if (str[tmp] && str[tmp][0] == '&' && !str[tmp][1])//si considerer comme error mettre lerreur ici
// 			*i = ++tmp;
// 		else
// 			tmp++;
// 	}
// }

// int	check_sep_exp(int i, int len, char **str)
// {
// 	if (i == 0 || (i > 0 && str[i - 1][0] == '&'))
// 	{
// 		while (++i < len)
// 		{
// 			if (str[i] && str[i][0] == '|' && !str[i][1])
// 				return (0);
// 			if (str[i] && (str[i][0] == '&'
// 				|| (str[i][1] && str[i][1] == '|')))
// 				return (1);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_equal(char **str, int len)
// {
// 	int	i;
// 	int	verif;

// 	i = 0;
// 	find_esp(&i, len, str);
// 	while (i < len)
// 	{
// 		if (str[i])
// 		{
// 			if (check_sep_exp(i, len, str))
// 			{
// 				if (!ft_strncmp(str[i], "export", 7))
// 				{
// 					verif = ft_export(str, &i, len);
// 					if (!verif)
// 						return (0);
// 				}
// 				else if (!ft_strncmp(str[i], "unset", 6))
// 				{
// 					verif = ft_unset(str, &i, len);
// 					if (!verif)
// 						return (0);
// 				}
// 				else
// 					i++;
// 			}
// 			else
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (1);
// }
