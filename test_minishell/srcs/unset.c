/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:44:12 by lide              #+#    #+#             */
/*   Updated: 2022/09/07 14:33:49 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

//doit ajouter remove_quote

void	remove_g_var(void)
{
	t_var	*tmp;
	int		verif;

	verif = 0;
	tmp = g_var;
	if (g_var->next != NULL)
		g_var->next->before = g_var->before;
	if (g_var->before != NULL)
		g_var->before->next = g_var->next;
	if (g_var->next != NULL)
		g_var = g_var->next;
	else if (g_var->before != NULL)
		g_var = g_var->before;
	else
		verif = 1;
	free(tmp->name);
	free(tmp->value);
	if (verif)
	{
		tmp->name = NULL;
		tmp->value = NULL;
	}
}

int	ft_unset(char **str, int i, int len)
{
	int		verif;

	while (i < len)
	{
		if (str[i])
		{
			if (str[i][0] == '|' || str[i][0] == '&')
				break ;
			verif = check_g_var(str[i]);
			if (verif)
				remove_g_var();
		}
		i++;
	}
	return (0);
}

void	ft_cd_utils_minus(void)
{
	char	*tmp;

	ft_begin_var(&g_var);
	while (ft_strncmp_2(g_var->name, "OLDPWD", 7) != 0)
		g_var = g_var->next;
	if (ft_strncmp_2(g_var->name, "OLDPWD", 7) == 0)
	{
		printf("%s\n", g_var->value);
		tmp = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD", tmp);
		if (!tmp)
			exit(ft_exit_cd());
		chdir(g_var->value);
		ft_export(&tmp, 0, 1);
		tmp = getcwd(NULL, 0);
		tmp = ft_strjoin("PWD", tmp);
		if (!tmp)
			exit(ft_exit_cd());
		ft_export(&tmp, 0, 1);
	}
}

int	ft_exit_cd(void)
{
	perror("strjoin in cd");
	exit(1);
}
