/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:08:01 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/01 20:55:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_exit_malloc(void)
{
	printf("A malloc has crashed\n");
	return (1);
}
