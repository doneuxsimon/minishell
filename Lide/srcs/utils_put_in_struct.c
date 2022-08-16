/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_put_in_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:25 by lide              #+#    #+#             */
/*   Updated: 2022/08/16 20:46:41 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	put_pipe(t_list **cmd, char **str, int i)
{
	*cmd = (*cmd)->next;
	str[i] = NULL;
	return (0);
}

int	put_ft_and_opt(char **str, t_list **cmd, int *i)
{
	int	error;

	error = remove_quote(str, *i);
	if (!error)
		return (0);
	(*cmd)->ft = str[*i];
	str[*i] = NULL;
	if (str[(*i) + 1] && str[(*i) + 1][0] == '-')
	{
		error = remove_quote(str, ++(*i));
		if (!error)
			return (0);
		(*cmd)->opt = str[*i];
		str[*i] = NULL;
	}
	return (1);
}

int	ct_arg(char **str, int len, int i)
{
	int	tmp;
	int	words;

	words = 0;
	tmp = i - 1;
	while (++tmp < len)
	{
		if (str[tmp] && (str[tmp][0] == '|' || str[tmp][0] == '&'))
			break ;
		if (str[tmp] != NULL)
			words++;
	}
	return (words);
}

int check_bracket(char *str)
{
	int	i;
	int	verif;

	verif = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '{' && verif == 0)
			verif = 1;
		if (str[i] == '}' && verif == 1)
			verif = 2;
	}
	if (verif == 2)
		return (1);
	else
		return (0);
}

int	put_arg2(char **str, t_list **cmd, int *i, int len)
{
	int	tmp;
	int	error;

	tmp = 0;
	while (*i < len)
	{
		if (str[*i] && (str[*i][0] == '|' || str[*i][0] == '&'))
		{
			(*i)--;
			break ;
		}
		else if (str[*i])
		{
			if (!(check_bracket(str[*i]) && cmp_line("echo", (*cmd)->ft)))
				error = remove_quote(str, *i);
			else
				error = 1;
			if (!error)
				return (0);
			(*cmd)->arg[tmp++] = str[*i];
			str[*i] = NULL;
		}
		(*i)++;
	}
	return (1);
}

int	put_arg(char **str, t_list **cmd, int len, int *i)
{
	int	words;
	int	error;

	words = ct_arg(str, len, *i);
	(*cmd)->arg = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(*cmd)->arg)
		return (print_perror("put_in_arg"));
	(*cmd)->arg[words] = NULL;
	error = put_arg2(str, cmd, i, len);
	if (!error)
		return (0);
	return (1);
}
