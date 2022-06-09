/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/06/09 18:47:12 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Sdoneux/test.h"



int	check_quote(char *str, char s, char d)
{
	int i;
	int s_q;
	int d_q;

	i = -1;
	s_q = 0;
	d_q = 0;
	while (str[++i])
	{
		if (str[i] == s)
			s_q++;
		else if (str[i] == d)
			d_q++;
	}
	if (s_q == 0 && d_q == 0)
		return (0);
	else if (s_q <= 1 && d_q <= 1)
		return (1);
	else if (s_q % 2 = 0 && d_q % 2 = 0)
		return (2);
	else
		return (3);
}

t_list *init_lst(void)
{
	t_list *list;

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
	int		i = -1;
	int		verif;
	t_list	*new;

	str = big_split(line, "&|");
	while (str[++i])
	{
		new = init_lst();
		//free si error;
		check_quote(str[i], '\'', '\"');
		//isoler les quotes et les mettres dans l'endroit approprier
	}
		// printf("%s\n", str[i]);
}

int	main(void)
{
	char	*line;
	char	*path;
	char	*tmp;

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
