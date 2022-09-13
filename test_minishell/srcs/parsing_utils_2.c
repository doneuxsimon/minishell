/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:27:47 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/12 19:15:34 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_echo(t_list *list)
{
	int	i;
	int	n;

	i = 0;
	n = ft_compare_n2(list);
	while (list->arg[i])
	{
		if (n == 1)
		{
			i = ft_skip_n(list, i, n);
			n = 2;
		}
		printf("%s", list->arg[i]);
		if (list->arg[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}

int	verif_builtin(t_list *list)
{
	int	i;

	i = 0;
	if (ft_strncmp_2(list->ft, "env", 4) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "exit", 5) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "export", 6) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "unset", 6) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "pwd", 4) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "echo", 5) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "cd", 3) == 0)
		i = 1;
	else if (ft_strncmp_2(list->ft, "./minishell", 12) == 0)
		i = 2;
	return (i);
}

void	ft_cd(t_list *list)
{
	char	*tmp;

	if (list->opt && ft_strncmp_2(list->opt, "-", 2) == 0 && !list->opt[1])
		ft_cd_utils_minus();
	else if (list->arg)
	{
		tmp = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD", tmp);
		if (!tmp)
			exit(ft_exit_cd());
		if (chdir(list->arg[0]) < 0)
			printf("minishel: cd: %s: no such file or directory\n",
				list->arg[0]);
		else
			ft_cd_utils2(tmp);
	}
	else
		ft_cd_utils();
}

void	ft_unset_old(void)
{
	char	*path;

	path = malloc(sizeof(char *) * 7);
	if (!path)
	{
		free_envp();
		exit(EXIT_FAILURE);
	}
	path = "OLDPWD";
	ft_unset(&path, 0, 1);
}
