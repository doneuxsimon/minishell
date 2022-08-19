/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_put_in_struct2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:55:16 by lide              #+#    #+#             */
/*   Updated: 2022/08/17 18:55:56 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	find_minus_quote(char **str, int *i, char *quote, char *other)
{
	if (str[(*i) + 1][0] == '\"')
		*quote = '\"';
	else if (str[(*i) + 1][0] == '\'')
		*quote = '\'';
	if (*quote == '\"')
		*other = '\'';
	else if (*quote == '\'')
		*other = '\"';
}

int	check_minus(char **str, int *i)
{
	int		j;
	int		verif;
	char	quote;
	char	other;

	verif = 0;
	quote = '\0';
	other = '\0';
	j = -1;
	if (!str[(*i) + 1])
		return (0);
	find_minus_quote(str, i, &quote, &other);
	while (str[(*i) + 1][++j] && str[(*i) + 1][j] == quote)
		verif++;
	if (!str[(*i) + 1][j] || str[(*i) + 1][j] != '-')
		return (0);
	while (str[(*i) + 1][++j] && str[(*i) + 1][j] != other)
		if (str[(*i) + 1][j] == quote)
			verif++;
	if (str[(*i) + 1][j] && str[(*i) + 1][j] == other)
		return (0);
	if (verif % 2 != 0)
		return (0);
	return (1);
}
