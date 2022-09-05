/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:44:36 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 21:45:29 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_print_delete(t_var **var)
{
	t_var	*tmp;

	printf("declare -x %s=\"%s\"\n", (*var)->name, (*var)->value);
	tmp = (*var);
	if ((*var)->next)
		(*var)->next->before = (*var)->before;
	if ((*var)->before)
		tmp->before->next = (*var)->next;
	(*var) = (*var)->next;
	free(tmp->value);
	free(tmp->name);
	free(tmp);
	if (!(*var)->next && !(*var)->before)
		*var = NULL;
}

int	check_w_sp(char *str, int j)
{
	int	i;

	i = -1;
	if (j == 0)
	{
		printf(ERROR_EXPORT, str);
		return (-1);
	}
	while (++i < j)
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		{
			printf(ERROR_EXPORT, str);
			return (-1);
		}
	}
	return (j);
}
