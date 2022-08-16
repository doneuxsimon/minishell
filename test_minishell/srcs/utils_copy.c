/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:08:35 by lide              #+#    #+#             */
/*   Updated: 2022/08/16 22:27:05 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

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
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] != '\0' && s2[i] != '\0')
		{
			n--;
			i++;
		}
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

int	ft_strncmp_end(char *s1, char *s2, int n)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while(s2[j])
		j++;
	while ((unsigned char)s1[i] == (unsigned char)s2[j])
		{
			n--;
			i--;
			j--;
		}
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (1);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * (len1(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

char*	print_str_perror(char *str)
{
	perror(str);
	return (NULL);
}

int	print_perror(char *str)
{
	perror(str);
	return (0);
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (0);
}
