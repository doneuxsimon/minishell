/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:44:12 by lide              #+#    #+#             */
/*   Updated: 2022/07/20 15:34:47 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

//doit ajouter remove_quote

void	remove_g_var(void)
{
	t_var	*tmp;
	int		verif;

	verif = 0;
	tmp = g_var;
	if (g_var->next != NULL)
		g_var->next->before = g_var->before;
	if (g_var->before != NULL)
		g_var->before->next = g_var->next;
	if (g_var->next != NULL)
		g_var = g_var->next;
	else if (g_var->before != NULL)
		g_var = g_var->before;
	else
		verif = 1;
	free(tmp->name);
	free(tmp->value);
	if (verif)
	{
		tmp->name = NULL;
		tmp->value = NULL;
	}
}

char	*remove_first_quote(char **str, int i)
{
	int		len;
	char	*tmp;
	int		ct;
	int		j;

	ct = -1;
	j = -1;
	len = len1(str[i]);
	if (str[i][0] == '\'' || str[i][0] == '\"')
	{
		len--;
		ct++;
	}
	tmp = (char *)malloc(sizeof(char) * (len - ct));
	if (!tmp)
		return (NULL);
	while (++ct < len)
		tmp[++j] = str[i][ct];
	return (tmp);
}

int	ft_unset(char **str, int *i, int len)
{
	int		verif;

	while (++(*i) < len)
	{
		if (str[*i])
		{
			if (str[*i][0] == '|' || str[*i][0] == '&')
				break ;
			verif = check_g_var(str[*i]);
			if (verif)
				remove_g_var();
		}
	}
	return (1);
}
