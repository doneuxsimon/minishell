/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/07/13 17:34:45 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	put_in_cmd(char **str, t_list **cmd, int len)
{
	int	i;
	int	tmp;
	int	words;

	words = 0;
	i = 0;
	while (i < len && !str[i])
		i++;
	(*cmd)->ft = str[i];
	str[i] = NULL;
	if (i + 1 < len && str[i + 1][0] == '-')
	{
		(*cmd)->opt = str[++i];
		str[i] = NULL;
	}
	tmp = i;
	while (++tmp < len)
		if (str[tmp] != NULL)
			words++;
	tmp = 0;
	(*cmd)->arg = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(*cmd)->arg)
		return (0);
	while(++i < len)
	{
		if (str[i])
		{
			(*cmd)->arg[tmp++] = str[i];
			str[i] = NULL;
		}
	}
	(*cmd)->arg[tmp] = 0;
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
		while (tmp->arg[++i])
			free(tmp->arg[i]);
		free(tmp);
	}
}

int	put_in_struct(char **str, t_list **cmd)
{
	int	len;
	int	i;

	i = -1;
	len = len2(str);
	if (!check_equal(str, len))
		return (0);
	redirection(str, cmd, len);
	if (!put_in_cmd(str, cmd, len))
		return (0);
	while (++i < len)
		printf("%s\n", str[i]);
	while ((*cmd)->next != NULL)
	{
		printf("%s / %s /", (*cmd)->ft, (*cmd)->opt);
		i = -1;
		while ((*cmd)->arg[++i])
			printf("%s /", (*cmd)->arg[i]);
		printf("%s / %s / %d / %d / %d\n", (*cmd)->link, (*cmd)->tmp, (*cmd)->infile, (*cmd)->outfile, (*cmd)->pos);
	}
	printf("%s / %s /", (*cmd)->ft, (*cmd)->opt);
	i = -1;
	while ((*cmd)->arg[++i])
	printf("%s /", (*cmd)->arg[i]);
	printf("%s / %s / %d / %d / %d\n", (*cmd)->link, (*cmd)->tmp, (*cmd)->infile, (*cmd)->outfile, (*cmd)->pos);
	free_all(cmd); // dois trouver ou reinitialiser la prochaine commande!!!
	// while (g_var->before != NULL)
	// 	g_var = g_var->before;
	// while (g_var->next != NULL)
	// {
	// 	printf("name = %s| value = %s\n", g_var->name, g_var->value);
	// 	g_var = g_var->next;
	// }
	// printf("name = %s| value = %s\n", g_var->name, g_var->value);
	return (1);
}
