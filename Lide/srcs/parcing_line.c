/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/07/15 17:16:21 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

//doit faire une copie de env et l'utiliser pour etre modifier dans unset et export;
//placer le reste des mots dans la structure
//gerer les free et les messages d'erreurs

char	**get_line(char *line)
{
	char	**str;
	int		i;

	i = -1;
	str = mini_split(line);
	if (!str)
	{
		printf("Error\n");
		return (NULL);
	}
	str = check_env(str);
	if (!str)
	{
		printf("Error2\n");
		return (NULL);
	}
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

int	ct_char(char *str)
{
	int		j;
	int		len;
	char	quote;

	j = -1;
	len = 0;
	quote = '\0';
	while (str[++j])
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			quote = str[j];
			while (str[++j] != quote)
				len++;
		}
		else
			len++;
	}
	if (!quote)
		return (-1);
	return (len);
}

char	*remove_unwanted_quote(char **str, int i, int ct)
{
	int		j;
	int		x;
	char	quote;
	char	*tmp;

	j = -1;
	x = 0;
	tmp = (char *)malloc(sizeof(char) * (ct + 1));
	if (!tmp)
		return (NULL);
	while (str[i][++j])
	{
		if (str[i][j] == '\'' || str[i][j] == '\"')
		{
			quote = str[i][j];
			while (str[i][++j] != quote)
				tmp[x++] = str[i][j];
		}
		else
			tmp[x++] = str[i][j];
	}
	tmp[x] = '\0';
	return (tmp);
}

int	remove_quote(char **str, int i)
{
	int		ct;
	char	*tmp;

	// printf("%d\n", i);
	ct = ct_char(str[i]);
	if (ct != -1)
	{
		tmp = remove_unwanted_quote(str, i, ct);
		if (!tmp)
		{
			printf("hello\n");
			return (0);
		}
		free(str[i]);
		str[i] = tmp;
	}
	return (1);
}

void	free_envp(void)
{
	while (g_var->next != NULL)
	{
		free(g_var->name);
		free(g_var->value);
		g_var = g_var->next;
	}
	free(g_var->name);
	free(g_var->value);
	free(g_var);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa1;
	char				*line;
	char				**str;
	int					i;
	t_list				*cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	g_var = init_var(g_var);
	ft_export(envp, &i, len2(envp));//gerer leaks export
	sa1.sa_handler = &test;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa1, NULL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = init_lst(cmd);
		line = readline("Minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			free_envp();
			rl_clear_history();
			exit(0);
		}
		add_history(line);
		str = get_line(line);
		if (str)
		{
			// i = remove_quote(str);
			// if (i)
				put_in_struct(str, &cmd);
		}
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
