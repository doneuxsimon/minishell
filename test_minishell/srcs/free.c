/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:35:04 by lide              #+#    #+#             */
/*   Updated: 2022/08/18 20:21:24 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*free_env(char *str, char *ret, char *env)
{
	free(str);
	free(env);
	return (ret);
}

char	*free_char(char *str, char *print)
{
	free(str);
	perror(print);
	return (NULL);
}

int	free_redirection(char **str, t_list **cmd, int len)
{
	free_all(cmd, 1);
	free_split(str, len);
	return (0);
}

void	free_all(t_list **cmd, int verif)
{
	t_list	*tmp;
	int		i;

	while ((*cmd)->before != NULL)
		*cmd = (*cmd)->before;
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp->ft);
		free(tmp->opt);
		if (!verif)
			free(tmp->link);
		unlink(tmp->tmp);
		free(tmp->tmp);
		i = -1;
		if (tmp->arg != NULL)
			while (tmp->arg[++i])
				free(tmp->arg[i]);
		free(tmp->arg);
		free(tmp);
	}
}

int	free_infile(char **str, int *i)
{
	free(str[*i]);
	str[(*i)++] = NULL;
	free(str[*i]);
	str[*i] = NULL;
	return (1);
}
