/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/09/12 18:06:19 by sdoneux          ###   ########.fr       */
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
		free_all(cmd, 0);
		free_split(str, len);
		return (0);
	}
	free(str);
	return (1);
}
