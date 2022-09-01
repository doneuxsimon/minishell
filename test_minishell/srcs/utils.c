/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:08:35 by lide              #+#    #+#             */
/*   Updated: 2022/09/01 15:09:26 by lide             ###   ########.fr       */
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
		&& s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
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

void	ft_close_pipe(t_exec_pipe *exec)
{
	close(exec->piped1[0]);
	close(exec->piped1[1]);
	pipe(exec->piped1);
}
