/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:47:39 by marvin            #+#    #+#             */
/*   Updated: 2022/08/23 19:19:08 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	init_global(char **envp)
{
	int	i;

	g_var = init_var(g_var);
	if (!g_var)
		return (1);
	g_var->returned = init_returned();
	if (!g_var->returned)
	{
		free(g_var);
		perror("init_returned");
		return (1);
	}
	i = ft_export(envp, &i, len2(envp));
	if (i)
	{
		free_envp();
		return (1);
	}
	return (0);
}

void	ft_start(char *str, t_list *cmd, char *path, char **envp)
{
	int	j;

	j = 0;
	if (put_in_struct(str, &cmd))
		return ;
	if (cmd->ft && ft_strncmp_2(cmd->ft, "cd", 3) == 0 && !cmd->next)
	{
		if (cmd->arg)
			chdir(cmd->arg[0]);
		else
			chdir(getenv("HOME"));
	}
	else if (cmd->ft && ft_strncmp_2(cmd->ft, "export", 7) == 0 && !cmd->next)
	{
		ft_export(cmd->arg, &j, len2(cmd->arg));
		j = 0;
	}
	else if (cmd->ft && ft_strncmp_2(cmd->ft, "unset", 6) == 0 && !cmd->next)
	{
		ft_unset(cmd->arg, &j, len2(cmd->arg));
		j = 0;
	}
	else
		ft_start_exec(cmd, path, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	char				**str;
	char				*path;
	t_list				*cmd;
	static int			ct_line;

	if (argc > 1)
	{
		printf("there are to much arguments\n");
		return (1);
	}
	(void)argv;
	cmd = NULL;
	if (init_global(envp))
		return (1);
	path = getenv("PATH");
	while (1)
	{
		sig(1);
		ct_line++;
		cmd = init_lst(cmd, ct_line);
		if (!cmd)
		{
			free_envp();
			return (1);
		}
		line = readline("Minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			free_envp();
			free(cmd);
			rl_clear_history();
			return (0);
		}
		add_history(line);
		str = get_line(line);
		if (str)
			ft_start(str, cmd, path, envp);
		else
			free(cmd);
	}
	return (0);
}
