/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_dol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:37:40 by lide              #+#    #+#             */
/*   Updated: 2022/06/15 16:38:15 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*free_env(char *str, char *ret)
{
	free(str);
	return (ret);
}

int	len1(char *str)
{
	int	ct;

	if (!str)
		return (0);
	ct = 0;
	while (str[ct])
		ct++;
	return (ct);
}

int	len2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
