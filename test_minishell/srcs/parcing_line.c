/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 14:46:06 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_sep(char **str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (str[i][0] && str[i][0] == '&' && !str[i][1])
			return (0);
		else if (str[i][0] && str[i][1] && !str[i][2]
			&& ((str[i][0] == '&' && str[i][1] == '&')
			|| (str[i][0] == '|' && str[i][1] == '|')))
			return (0);
	}
	return (1);
}


char	**get_line(char *line)
{
	char	**str;
	int		len;

	str = mini_split(line);
	if (!str)
		return (NULL);
	len = len2(str);
	str = check_dol(str, len);
	if (!str)
		return (NULL);
	len = len2(str);
	if (!check_sep(str, len))
	{
		printf("you can only use '|' has a separator\n");
		free_split(str, len);
		return (NULL);
	}
	if (str[0] && str[0][0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		free_split(str, len);
		return (NULL);
	}
	return (str);
}

void	free_envp(void)
{
	t_var	*tmp;

	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		tmp = g_var;
		g_var = g_var->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(g_var->returned);
	free(g_var->name);
	free(g_var->value);
	free(g_var);
}

int	*init_returned(void)
{
	int	*i;

	i = (int *)malloc(sizeof(int));
	*i = 0;
	return (i);
}

int	command_exist(t_list *list, char **cmd_path)
{
	if (!get_cmd2(cmd_path, list->ft) && !verif_builtin(list))
	{
		g_var->returned[0] = 127;
		printf("minishell: %s: Command not found\n", list->ft);
		return (0);
	}
	while (list->next)
	{
		list = list->next;
		if (!get_cmd2(cmd_path, list->ft) && !verif_builtin(list))
		{
			g_var->returned[0] = 127;
			printf("minishell: %s: Command not found\n", list->ft);
			return (0);
		}
	}
	return (1);
}
