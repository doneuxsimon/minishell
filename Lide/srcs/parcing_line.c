/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/06/23 15:27:21 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_list	*init_lst(t_list *cmd)
{
	cmd = (t_list *)malloc(sizeof(t_list));
	if (!cmd)
		return (NULL);
	cmd->ft = NULL;
	cmd->opt = NULL;
	cmd->arg = NULL;
	cmd->link = NULL;
	cmd->tmp = NULL;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->pos = 0;
	cmd->next = NULL;
	cmd->before = NULL;
	return (cmd);
}

char	**get_line(char *line)
{
	char	**str;
	int		i;

	i = -1;
	str = mini_split(line);
	if (!str)
		printf("Error\n");
	if (str)
		str = check_env(str);
	if (!str)
		printf("Error2\n");
	// else
	// 	while (str[++i])
	// 		printf("%s\n", str[i]);
	return (str);
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
	char				**str;
	int					i;
	t_list				*cmd;
	t_var				*var;

	cmd = NULL;
	var = NULL;
	init_var(&g_var);
	sa1.sa_handler = &test;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa1, NULL);
	signal(SIGQUIT, SIG_IGN);
	cmd = init_lst(cmd);
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
		str = get_line(line);
		put_in_struct(str, &cmd, &var);
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
