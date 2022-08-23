/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_var_to_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:48:33 by lide              #+#    #+#             */
/*   Updated: 2022/08/23 18:12:56 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	len_g_var(void)
{
	int	len;

	len = 1;
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		g_var = g_var->next;
		len ++;
	}
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (len1(s1) + len1(s2) + 2));
	if (!s3)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
	{
		s3[i] = s1[i];
	}
	s3[i++] = '=';
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}

void	*free_join(char **str, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(str[j]);
	free(str);
	return (NULL);
}

char	**g_var_to_char(void)
{
	int		len;
	char	**str;
	char	*tmp;
	int		i;

	i = -1;
	len = len_g_var();
	str = (char **)malloc(sizeof(char *) * len + 1);
	if (!str)
		return (NULL);
	str[len + 1] = NULL;
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (--len > 0)
	{
		tmp = ft_strjoin(g_var->name, g_var->value);
		if (!tmp)
			return (free_join(str, i));
		str[++i] = tmp;
		g_var = g_var->next;
	}
	return (str);
}
