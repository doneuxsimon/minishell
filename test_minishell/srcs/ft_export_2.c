/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:02:09 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/05 21:45:37 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_var_cmp(t_var *tmp, t_var *clean)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((unsigned char)tmp->name[i] == (unsigned char)clean->name[i])
			i++;
		else if ((unsigned char)tmp->name[i] < (unsigned char)clean->name[i])
			return (0);
		else if ((unsigned char)tmp->name[i] > (unsigned char)clean->name[i])
			return (1);
	}
	return (0);
}

void	free_cp_var(int verif, t_var *new)
{
	t_var	*tmp;

	while (new->before != NULL)
		new = new->before;
	while (new->next != NULL)
	{
		tmp = new;
		new = new->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(new->name);
	if (verif)
		free(new->value);
	free(new);
}

void	copy_var_struct(t_var **new, t_var **tmp, t_var **cp)
{
	(*new)->next = *tmp;
	(*tmp)->before = *new;
	*new = (*new)->next;
	*cp = (*cp)->next;
}

t_var	*copy_var(void)
{
	t_var	*new;
	t_var	*tmp;
	t_var	*cp;

	new = NULL;
	new = init_var(new);
	if (!new)
		return (NULL);
	ft_begin_var(&g_var);
	cp = g_var;
	while (cp->value)
	{
		tmp = NULL;
		new->name = ft_strdup(cp->name);
		if (!new->name)
			free_cp_var(0, new);
		new->value = ft_strdup(cp->value);
		if (!new->value)
			free_cp_var(1, new);
		tmp = init_var(tmp);
		if (!new)
			free_cp_var(1, new);
		copy_var_struct(&new, &tmp, &cp);
	}
	return (new);
}

void	ft_export_2(void)
{
	t_var	*tmp;
	t_var	*clean;

	clean = copy_var();
	if (!clean)
		exit(EXIT_FAILURE);
	ft_begin_var(&clean);
	while (clean)
	{
		ft_begin_var(&clean);
		tmp = clean;
		while (clean->next->name != NULL)
		{
			clean = clean->next;
			if (ft_var_cmp(tmp, clean))
				tmp = clean;
		}
		ft_print_delete(&tmp);
		clean = tmp;
		if (clean)
			ft_begin_var(&clean);
	}
}
