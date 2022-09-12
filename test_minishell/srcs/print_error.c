/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:52 by lide              #+#    #+#             */
/*   Updated: 2022/09/12 14:15:15 by sdoneux          ###   ########.fr       */
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
	else
	{
		if (ct == 3)
			printf("minishel: syntax error near unexpected token `%c'\n", sep);
		else
			printf("minishel: syntax error near unexpected token `%c%c'\n",
				sep, sep);
	}
}

int	change_question_error(char **str, char *nb, int i, int verif)
{
	if (!verif)
		str[i] = print_str_perror("ft_itoa");
	else
		str[i] = free_char(nb, "change_question\n");
	return (0);
}
