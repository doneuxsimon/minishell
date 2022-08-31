/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:02:09 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/31 19:58:25 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_tmp(t_var *clean)
{
	t_var	*tmp;

	while (clean->before != NULL)
		clean = clean->before;
	while (clean->next != NULL)
	{
		tmp = clean;
		clean = clean->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(clean->name);
	free(clean->value);
	free(clean);
}

t_var	*init_clean(void)
{
	t_var	*var;
	t_var	*tmp;

	tmp = NULL;
	var = NULL;
	var = init_var(var);
	ft_begin_var(&g_var);
	while (g_var->next)
	{
		var->name = strdup(g_var->name);
		var->value = strdup(g_var->value);
		var->next = init_var(tmp);
		var->next->before = var;
		var = var->next;
		g_var = g_var->next;
	}
	ft_begin_var(&var);
	return (var);
}

int	ft_var_cmp(t_var *tmp, t_var *clean)
{
	int	i;

	i = 0;
	while (i)
	{
		if (tmp->name[i] == clean->name[i])
			i++;
		else if (tmp->name[i] > clean->name[i])
			return (0);
		else if (tmp->name[i] < clean->name[i])	
			return (1);
	}
	return (0);
}

void	ft_print_delete(t_var **var)
{
	t_var	*tmp;

	printf("declare - x %s=%s\n", (*var)->name, (*var)->value);
	tmp = (*var);
	(*var)->next->before = (*var)->before;
	tmp->before->next = (*var)->next;
	(*var) = (*var)->next;
	free(tmp->value);
	free(tmp->name);
}

void	ft_export_2(void)
{
	t_var	*tmp;
	t_var	*clean;

	ft_begin_var(&g_var);
	clean = init_clean();
	if (!clean)
		exit(EXIT_FAILURE);
	ft_begin_var(&clean);
	while (clean)
	{
		tmp = clean;
		while (clean->next)
		{
			clean =clean->next;
			if (ft_var_cmp(tmp, clean))
				tmp = clean;
		}
		ft_print_delete(&tmp);
		ft_begin_var(&clean);
	}
}