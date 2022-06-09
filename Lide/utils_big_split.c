/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_big_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:51:14 by lide              #+#    #+#             */
/*   Updated: 2022/06/09 17:52:14 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Sdoneux/test.h"

int	in_tab(char str, char *c)
{
	int	i;

	i = -1;
	while (c[++i])
	{
		if (str == c[i])
			return (0);
	}
	return (1);
}

int	ft_pass(char const *s, char *c, int i)
{
	int	nb;

	nb = in_tab(s[i], c);
	while (s[i] && nb == 0)
	{
		i++;
		if (s[i])
			nb = in_tab(s[i], c);
	}
	return (i);
}
