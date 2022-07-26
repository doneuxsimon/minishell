/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/07/26 19:21:19 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	put_in_cmd(char **str, t_list **cmd, int len)
{
	int	i;
	int	verif;

	i = -1;
	verif = 0;
	while ((*cmd)->before != NULL)
		*cmd = (*cmd)->before;
	while (++i < len)
	{
		if (str[i] && (str[i][0] == '|' || str[i][0] == '&'))
			verif = put_pipe(cmd, str, i);
		else if (str[i] && verif == 0)
		{
			verif = put_ft_and_opt(str, cmd, &i);
			if (!verif)
				return (0);
		}
		else if (str[i])
		{
			verif = put_arg(str, cmd, len, &i);
			if (!verif)
				return (0);
		}
	}
	return (1);
}

void	print_cmd(t_list **cmd)
{
	int	i;

	while ((*cmd)->before != NULL)
		*cmd = (*cmd)->before;
	while ((*cmd)->next != NULL)
	{
		printf("%s / %s /", (*cmd)->ft, (*cmd)->opt);
		i = -1;
		if ((*cmd)->arg != NULL)
			while ((*cmd)->arg[++i])
				printf("%s /", (*cmd)->arg[i]);
		printf("%s / %s / %d / %d / %d\n", (*cmd)->link, (*cmd)->tmp, (*cmd)->infile, (*cmd)->outfile, (*cmd)->pos);
		*cmd = (*cmd)->next;
	}
	printf("%s / %s /", (*cmd)->ft, (*cmd)->opt);
	i = -1;
	if ((*cmd)->arg != NULL)
		while ((*cmd)->arg[++i])
			printf("%s /", (*cmd)->arg[i]);
	printf("%s / %s / %d / %d / %d\n", (*cmd)->link, (*cmd)->tmp, (*cmd)->infile, (*cmd)->outfile, (*cmd)->pos);
	free_all(cmd);
}

void	print_env(void)
{
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		printf("name = %s| value = %s\n", g_var->name, g_var->value);
		g_var = g_var->next;
	}
	printf("name = %s| value = %s\n", g_var->name, g_var->value);
}

int	put_in_struct(char **str, t_list **cmd)
{
	int	len;
	int	verif;

		len = len2(str);
	verif = redirection(str, cmd, len);
	if (!verif)
		return (0);
	if (!put_in_cmd(str, cmd, len))
	{
		free_envp();
		free_all(cmd);
		free_split(str, len);
		return (0);
	}
	// while (++i < len)
	// 	printf("%s\n", str[i]);
	free(str);
	print_cmd(cmd);
	// print_env();
	return (1);
}
