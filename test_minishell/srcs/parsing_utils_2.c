/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:27:47 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/31 17:16:18 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_echo(t_list *list)
{
	int	i;
	int	x;
	int	n;

	i = 0;
	x = 0;
	n = ft_compare_n2(list);
	while (list->arg[i])
	{
		if (n)
			printf("%s", list->arg[i]);
		if (list->arg[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}
