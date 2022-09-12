/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:44:36 by lide              #+#    #+#             */
/*   Updated: 2022/09/12 17:04:56 by sdoneux          ###   ########.fr       */
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

char	*get_cmd2_utils(char **cmd_paths, char *cmd)
{
	char	*cmd2;

	cmd2 = get_cmd_utils(cmd_paths, cmd);
	if (cmd2 && ft_strncmp_2(cmd2, "MALLOC ERROR", 13) == 0)
		return (NULL);
	else if (cmd2)
		return (cmd2);
	else
		return (NULL);
}
