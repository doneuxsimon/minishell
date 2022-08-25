/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:27:47 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/25 15:51:51 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_print_code(t_list *list, int i, int *j)
{
	while (list->arg[i][(*j)])
	{
		if (list->arg[i][(*j)] == '$' && list->arg[i][(*j) + 1]
			&& list->arg[i][(*j) + 1] == '?')
		{
			printf("%d", g_var->returned[0]);
			(*j) += 2;
		}
		else
		{
			printf("%c", list->arg[i][(*j)]);
			(*j)++;
		}
	}
}

int	ft_search_dollar(t_list *list, int i, int *j)
{
	int	x;

	x = 0;
	if (list->arg[i][(*j)] == '$' && list->arg[i][(*j) + 1]
		&& list->arg[i][(*j) + 1] == '?')
	{
		ft_print_code(list, i, j);
		x = 1;
		printf(" ");
	}
	(*j)++;
	return (x);
}

void	ft_echo(t_list *list)
{
	int	i;
	int	j;
	int	x;
	int	n;

	i = 0;
	x = 0;
	n = ft_compare_n2(list);
	while (list->arg[i])
	{
		if (n)
			i = ft_skip_n(list, i, n);
		j = 0;
		while (list->arg[i][j])
			x = ft_search_dollar(list, i, &j);
		if (x == 0)
		{
			printf("%s", list->arg[i]);
			if (list->arg[i + 1])
				printf(" ");
		}
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	ft_cd(t_list *list)
{
	chdir(list->arg[0]);
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}
