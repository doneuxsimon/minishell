/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:51:03 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/12 19:12:32 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_compare_n2(t_list *list)
{
	int	i;
	int	n;

	n = 1;
	i = 1;
	if (!list->opt)
		return (0);
	if (list->opt[0] != '-')
		return (0);
	while (list->opt[i])
	{
		if (list->opt[i] != 'n')
			n = 0;
		i++;
	}
	if (n == 0)
	{
		write(2, list->opt, ft_strlen(list->opt));
		if (!list->arg)
			write(2, "\n", 1);
		else
			write(2, " ", 1);
	}
	return (n);
}

int	ft_skip_n(t_list *list, int i, int n)
{
	while (ft_compare_n(list->arg[i]) && n)
	{
		n = ft_compare_n(list->arg[i]);
		i++;
	}
	return (i);
}

int	dup0(t_list *list, int piped)
{
	if (list->infile)
	{
		if (dup2(list->infile, 0) == -1)
			return (-1);
	}
	else
	{
		if (dup2(piped, 0) == -1)
			return (-1);
	}
	return (0);
}

int	dup1(t_list *list, int piped)
{
	if (list->outfile)
	{
		if (dup2(list->outfile, 1) == -1)
			return (-1);
	}
	else
	{
		if (dup2(piped, 1) == -1)
			return (-1);
	}
	return (0);
}

void	ft_cd_utils(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD", tmp);
	if (!tmp)
	{
		perror("strjoin in cd");
		exit(1);
	}
	if (chdir(getenv("HOME")) < 0)
		perror("minishel: cd: ");
	else
		ft_cd_utils2(tmp);
}
