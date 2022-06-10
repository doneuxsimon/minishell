/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/06/10 19:30:09 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_list	*init_lst(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->ft = NULL;
	list->opt = NULL;
	list->arg = NULL;
	list->file = NULL;
	list->next = NULL;
	list->before = NULL;
	return (list);
}

void	get_line(char *line)
{
	char	**str;
	int		i;

	i = -1;
	str = mini_split(line);
	if (!str)
		printf("Error\n");
	else
	{
		while (str[++i])
			printf("%s\n", str[i]);
	}
}

int	main(void)//voué a disparaitre
{
	char	*line;
	// char	*path;
	// char	*tmp;

	// path = getenv( "PATH" );
	while (1)
	{
		line = readline("Minishell $> ");
		add_history(line);
		get_line(line);
		// tmp = get_cmd(path, line);
		// printf("%s\n", tmp);
	}
	return (0);
}
