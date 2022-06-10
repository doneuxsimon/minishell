/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:01:34 by sdoneux           #+#    #+#             */
/*   Updated: 2022/06/10 18:40:31 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	words(char const *s, char *c)
{
	int	i;
	int	j;
	int	nb;
	int	tmp;

	tmp = 1;
	nb = 0;
	i = -1;
	while (s[++i])
	{
		j = in_tab(s[i], c);
		if (tmp == 1 && j)
		{
			nb++;
			tmp = 0;
		}
		if (j == 0)
			tmp = 1;
	}
	return (nb);
}

static int	letter(char const *s, char *c, int i)
{
	int	nb;
	int	j;

	nb = 0;
	j = in_tab(s[i], c);
	while (s[i] && j)
	{
		nb++;
		i++;
		j = in_tab(s[i], c);
	}
	return (nb);
}

static char	**ft_free(char **s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		free(s1[i]);
		i++;
	}
	free(s1);
	return (NULL);
}

static char	**ft_split2(char const *s, char *c, char **s1)
{
	int	j;
	int	j2;
	int	i;
	int	nb;

	j = 0;
	i = 0;
	while (s[i])
	{
		i = ft_pass(s, c, i);
		j2 = 0;
		if (s[i])
		{
			nb = letter(s, c, i);
			s1[j] = (char *)malloc(sizeof(char) * (nb + 1));
			if (!s1[j])
				return (ft_free(s1));
			s1[j][nb] = 0;
			while (s[i] && j2 < nb)
				s1[j][j2++] = s[i++];
			j++;
		}
	}
	s1[j] = NULL;
	return (s1);
}

char	**big_split(char const *s, char *c)
{
	int		sep;
	char	**s1;

	if (!s)
		return (NULL);
	sep = words(s, c);
	if ((!s[0] && !c) || sep == 0)
	{
		s1 = (char **)malloc(sizeof(char *));
		if (!s1)
			return (NULL);
		s1[0] = NULL;
		return (s1);
	}
	s1 = (char **)malloc(sizeof(char *) * (sep + 1));
	if (!s1)
		return (NULL);
	return (ft_split2(s, c, s1));
}
