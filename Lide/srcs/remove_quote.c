/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:26:35 by lide              #+#    #+#             */
/*   Updated: 2022/07/26 19:18:03 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ct_char(char *str)
{
	int		j;
	int		len;
	char	quote;

	j = -1;
	len = 0;
	quote = '\0';
	while (str[++j])
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			quote = str[j];
			while (str[++j] != quote)
				len++;
		}
		else
			len++;
	}
	if (!quote)
		return (-1);
	return (len);
}

char	*remove_unwanted_quote(char **str, int i, int ct)
{
	int		j;
	int		x;
	char	quote;
	char	*tmp;

	j = -1;
	x = 0;
	tmp = (char *)malloc(sizeof(char) * (ct + 1));
	if (!tmp)
		return (NULL);
	while (str[i][++j])
	{
		if (str[i][j] == '\'' || str[i][j] == '\"')
		{
			quote = str[i][j];
			while (str[i][++j] != quote)
				tmp[x++] = str[i][j];
		}
		else
			tmp[x++] = str[i][j];
	}
	tmp[x] = '\0';
	return (tmp);
}

int	remove_quote(char **str, int i)
{
	int		ct;
	char	*tmp;

	ct = ct_char(str[i]);
	if (ct != -1)
	{
		tmp = remove_unwanted_quote(str, i, ct);
		if (!tmp)
		{
			perror("remove_quote");
			return (0);
		}
		free(str[i]);
		str[i] = tmp;
	}
	return (1);
}
