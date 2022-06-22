/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/06/22 05:51:01 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

void	ft_export(char **str, t_list **var, int *i, int len)
{
	int j;

	(*i)++;
	while(*i < len)
	{
		if (str[*i] && (str[*i][0] == '|' || str[*i][0] == '&'))
			break ;
		if (str[*i])
		{
			j = -1;
			while (str[*i][++j])
			{
				if (str[*i][j] == '=')
				//mettre egalité dans variable global
				//else if check dans var
			}
		}
	}
}

void	check_equal(char **str, t_list **cmd, t_var **var, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		if (str[i])
		{
			if (!ft_strncmp(str[i], "export", 6))
				ft_export(str, var, &i, len);
			else if (find_equal(str[i]))
		}
		else
			i++;
	}
}

void	init_var(t_var **var)
{
	(*var)->name = NULL;
	(*var)->value = NULL;
	(*var)->next = NULL;
	(*var)->before = NULL;
}

void	put_in_struct(char **str, t_list **cmd, t_var **var)
{
	int	len;
	int	i;

	i = -1;
	init_var(var);
	len = len2(str);
	check_equal(str, cmd, var, len);
	redirection(str, cmd, len);
	while (++i < len)
		printf("%s\n", str[i]);
}
