/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/07/15 16:55:23 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	put_in_cmd(char **str, t_list **cmd, int len)//proteger quote
{
	int	i;
	int	verif;
	int	tmp;
	int	words;

	i = -1;
	verif = 0;
	words = 0;
	while ((*cmd)->before != NULL)
		*cmd = (*cmd)->before;
	while(++i < len)
	{
		if (str[i] && (str[i][0] == '|' || str[i][0] == '&'))
		{
			*cmd = (*cmd)->next;
			str[i] = NULL;
			verif = 0;
		}
		else if (str[i] && verif == 0)
		{
			remove_quote(str, i);
			(*cmd)->ft = str[i];
			str[i] = NULL;
			if (str[i + 1] && str[i + 1][0] == '-')
			{
				remove_quote(str, ++i);
				(*cmd)->opt = str[i];
				str[i] = NULL;
			}
			verif = 1;
		}
		else if (str[i])//refaire
		{
			tmp = i - 1;
			while (++tmp < len)
			{
				if (str[tmp] && (str[tmp][0] == '|' || str[tmp][0] == '&'))
					break;
				if (str[tmp] != NULL)
					words++;
			}
			tmp = 0;
			(*cmd)->arg = (char **)malloc(sizeof(char *) * (words + 1));
			if (!(*cmd)->arg)
				return (0);
			while(i < len)
			{
				if (str[i] && (str[i][0] == '|' || str[i][0] == '&'))
				{
					(*cmd)->arg[words] = NULL;
					i--;
					break;
				}
				else if (str[i])
				{
					remove_quote(str, i);
					(*cmd)->arg[tmp++] = str[i];
					str[i] = NULL;
				}
				i++;
			}
		}
	}
	return (1);
}

void	free_all(t_list **cmd)
{
	t_list *tmp;
	int i;

	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp->ft);
		free(tmp->opt);
		free(tmp->link);
		free(tmp->tmp);
		i = -1;
		if (tmp->arg != NULL)
			while (tmp->arg[++i])
				free(tmp->arg[i]);
		free(tmp);
	}
}

void	print_cmd(t_list **cmd)
{
	int i;

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
	int	i;

	i = -1;
	len = len2(str);
	// if (!check_equal(str, len))
	// 	return (0);
	redirection(str, cmd, len);
	if (!put_in_cmd(str, cmd, len))
		return (0);
	while (++i < len)
		printf("%s\n", str[i]);
	print_cmd(cmd);
	// print_env();
	return (1);
}
