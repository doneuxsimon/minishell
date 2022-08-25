/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:47:39 by marvin            #+#    #+#             */
/*   Updated: 2022/08/25 16:08:53 by sdoneux          ###   ########.fr       */
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

void	ft_start(char **str, t_list *cmd, char *path, char **envp)
{
	int	j;

	j = 0;
	if (!put_in_struct(str, &cmd))
		return ;
	if (cmd->ft && ft_strncmp_2(cmd->ft, "cd", 3) == 0 && !cmd->next)
	{
		if (cmd->arg)
			chdir(cmd->arg[0]);
		else
			chdir(getenv("HOME"));
	}
	else if (cmd->ft && ft_strncmp_2(cmd->ft, "exit", 5) == 0 && !cmd->next)
		ft_exit(cmd);
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
	free_all(&cmd, 0);
}

char	**start_parsing(t_list **cmd)
{
	static int	ct_line;
	char		*line;

	sig(1);
	ct_line++;
	*cmd = init_lst(*cmd, ct_line);
	if (!*cmd)
		return (NULL);
	line = readline("Minishell$ ");
	if (!line)
	{
		write(1, "exit\n", 5);
		free_envp();
		free(*cmd);
		rl_clear_history();
		exit (0);
	}
	add_history(line);
	return (get_line(line));
}

char	*ft_get_path(void)
{
	ft_begin_var(&g_var);
	while (g_var->next)
	{
		if (ft_strncmp_2("PATH", g_var->name, 5) == 0)
			return (g_var->value);
		else
			g_var = g_var->next;
	}
	if (ft_strncmp_2("PATH", g_var->name, 5) == 0)
		return (g_var->value);
	else
		return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char				**str;
	char				*path;
	t_list				*cmd;

	if (argc > 1)
	{
		printf("there are to much arguments\n");
		return (1);
	}
	(void)argv;
	cmd = NULL;
	if (init_global(envp))
		return (1);
	path = ft_get_path();
	while (1)
	{
		str = start_parsing(&cmd);
		if (str)
			ft_start(str, cmd, path, envp);
		else
			free(cmd);
	}
	return (0);
}
