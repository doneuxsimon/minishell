/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:52 by lide              #+#    #+#             */
/*   Updated: 2022/08/17 18:53:51 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*print_str_perror(char *str)
{
	perror(str);
	return (NULL);
}

int	print_perror(char *str)
{
	perror(str);
	return (0);
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	skip_sep_error(int ct, int sep)
{
	if (sep == '<')
	{
		if (ct == 4)
			printf("minishel: syntax error near unexpected token `<'\n");
		else if (ct == 5)
			printf("minishel: syntax error near unexpected token `<<'\n");
		else
			printf("minishel: syntax error near unexpected token `<<<'\n");
	}
	else if (sep == '>')
	{
		if (ct == 3)
			printf("minishel: syntax error near unexpected token `>'\n");
		else
			printf("minishel: syntax error near unexpected token `>>'\n");
	}
}
