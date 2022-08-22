/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:47:39 by marvin            #+#    #+#             */
/*   Updated: 2022/08/22 16:53:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	char				**str;
	char				*path;
	int					i;
	t_list				*cmd;
	static int			ct_line;
	int					j;


	(void)argc;
	(void)argv;
	cmd = NULL;
	i = 0;
	j = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	i = 0;
		while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	i = 0;
	if (!check_g_var2("SHLVL", "1"))
	{
		printf("yoyo\n");
		g_var = init_var(g_var);
		if (!g_var)
			return (1);
			g_var->returned = init_returned();
		if (!g_var->returned)
		{
			free(g_var);
			return (1);
		}
		i = ft_export(envp, &i, len2(envp));
		if (i)
		{
			free_envp();
			return(1);
		}
	}
	printf("ca commence\n");
	path = getenv("PATH");
	while (1)
	{
		sig(1);
		ct_line++;
		cmd = init_lst(cmd, ct_line);
		if (!cmd)
		{
			free_envp();
			return(1);
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
		{
			i = put_in_struct(str, &cmd);
			if (cmd->ft && ft_strncmp(cmd->ft, "cd", 3) == 0 && !cmd->next)
			{
				if (cmd->arg)
					chdir(cmd->arg[0]);
				else
					chdir(getenv("HOME"));
			}
			else if (cmd->ft && ft_strncmp(cmd->ft, "export", 7) == 0 && !cmd->next)
			{
				ft_export(cmd->arg, &j, len2(cmd->arg));
				j = 0;
			}
			else if (cmd->ft && ft_strncmp(cmd->ft, "unset", 6) == 0 && !cmd->next)
			{
				ft_unset(cmd->arg, &j, len2(cmd->arg));
				j = 0;
			}
			else
				ft_start_exec(cmd, path, envp);
		}
		else
			free(cmd);
	}
	return (0);
}