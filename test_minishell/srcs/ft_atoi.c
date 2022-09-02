/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:35:27 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/01 18:20:55 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static long	ft_isspace(const char *str, long i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	return (i);
}

static long	ft_issneg(const char *str, long *i, long isneg)
{
	if (str[*i] != '\0' && str[*i] == '-')
	{
		isneg = 1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (isneg);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	nbr;
	int		isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	i = ft_isspace(str, i);
	isneg = ft_issneg(str, &i, isneg);
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i++] - '0');
		if (isneg == 1 && nbr > 2147483648)
			return (0);
		if (isneg == 0 && nbr > 2147483647)
			return (-1);
	}
	if (isneg == 1)
		return (-nbr);
	return (nbr);
}

int	is_digitt(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1])
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
