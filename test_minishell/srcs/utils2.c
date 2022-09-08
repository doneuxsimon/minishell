/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:28:26 by lide              #+#    #+#             */
/*   Updated: 2022/09/08 20:34:37 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

char	**print_pipe_error(char *line)
{
	add_history(line);
	free(line);
	printf("minishell: syntax error near unexpected token `|'\n");
	return (NULL);
}
