/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/06/15 15:54:05 by lide             ###   ########.fr       */
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
	{
		printf("Error\n");
		exit(0);
	}
	str = check_env(str);
	if (!str)
		printf("Error2\n");
	else
		while (str[++i])
			printf("%s\n", str[i]);
}

void	test(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	struct sigaction	sa1;
	char				*line;
	int					i;

	sa1.sa_handler = &test;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa1, NULL);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			exit(0);
		}
		add_history(line);
		get_line(line);
	}
	return (0);
}

// int	main(void)//voué a disparaitre
// {
// 	char	*line;
// 	// char	*path;
// 	// char	*tmp;

// 	// path = getenv( "PATH" );
// 	while (1)
// 	{
// 		line = readline("Minishell $> ");
// 		add_history(line);
// 		get_line(line);
// 		// tmp = get_cmd(path, line);
// 		// printf("%s\n", tmp);
// 	}
// 	return (0);
// }
