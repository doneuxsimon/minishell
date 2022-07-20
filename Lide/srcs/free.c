/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:35:04 by lide              #+#    #+#             */
/*   Updated: 2022/07/20 18:39:22 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*free_env(char *str, char *ret, char *env)
{
	free(str);
	free(env);
	return (ret);
}

char	*free_char(char *str)
{
	free(str);
	return (NULL);
}

int	free_redirection(char **str, t_list **cmd, int len)
{
	//selon l'erreur mettre un msg
	free_envp();
	free_all(cmd);
	free_split(str, len);
	return (0);
}
