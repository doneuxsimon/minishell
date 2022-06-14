/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/06/14 18:00:39 by lide             ###   ########.fr       */
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

int	ft_len(char *str)
{
	int	ct;

	if (!str)
		return (0);
	ct = 0;
	while (str[ct])
		ct++;
	return (ct);
}

char	*change_env(char *str, int *j, int tmp)//doit changer tmp -1 = $
{
	char *line;
	char *env;
	int len;
	int i;
	int ct;

	len = (*j) - tmp;
	env = (char *)malloc(sizeof(char) * len + 1);
	if (!env)
	{
		free(str);
		return (NULL);
	}
	env[len] = '\0';
	i = -1;
	while (++i < len)
		env[i] = str[tmp + i];
	line = getenv(env);
	free(env);
	len = ft_len(str) + ft_len(line) - len;
	env = (char *)malloc(sizeof(char) * len);
	if (!env)
	{
		free(str);
		return (NULL);
	}
	len = ft_len(line);
	i = -1;
	ct = -1;
	while (++i < tmp - 1)
		env[i] = str[i];
	while (++ct < len)
		env[i++] = line[ct];
	ct = i;
	while(str[*j])
		env[i++] = str[(*j)++];
	*j = tmp - 1 + len;
	printf("%d\n", *j);
	free(str);
	return (env);
}

char **check_env(char **str)
{
	int	i;
	int	j;
	int tmp;

	i = -1;
	while(str[++i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'')
			{
				tmp = ++j;
				while (str[i][tmp] && str[i][tmp] != '\'')
					tmp++;
				if (str[i][tmp])
					j = ++tmp;
			}
			else if (str[i][j] == '$')
			{
				tmp = ++j;
				while (str[i][j] && check_expt(str[i][j], 4))
					j++;
				str[i] = change_env(str[i], &j, tmp);
			}
			else
				j++;
		}
	}
	return (str);
}

void	get_line(char *line)
{
	char	**str;
	int		i;

	i = -1;
	str = mini_split(line);
	str = check_env(str);
	if (!str)
		printf("Error\n");
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
	while (i++ < 10)
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
