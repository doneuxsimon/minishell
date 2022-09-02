/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:47:39 by marvin            #+#    #+#             */
/*   Updated: 2022/09/02 18:06:44 by lide             ###   ########.fr       */
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
	i = ft_export(envp, 0, len2(envp));
	if (i)
	{
		free_envp();
		return (1);
	}
	return (0);
}

void	ft_start(char **str, t_list *cmd, char *path, char **envp)
{
	if (!put_in_struct(str, &cmd))
		return ;
	ft_begin(&cmd);
	if (cmd->ft && ft_strncmp_2(cmd->ft, "cd", 3) == 0
		&& !cmd->before && !cmd->next)
		ft_cd(cmd);
	else if (cmd->ft && ft_strncmp_2(cmd->ft, "exit", 5) == 0
		&& !cmd->before && !cmd->next)
		ft_exit(cmd);
	else if (cmd->ft && ft_strncmp_2(cmd->ft, "export", 7) == 0
		&& !cmd->before && !cmd->next)
	{
		if (cmd->arg)
			ft_export(cmd->arg, 0, len2(cmd->arg));
		else if (!cmd->arg)
			ft_export_2();
	}
	else if (cmd->ft && ft_strncmp_2(cmd->ft, "unset", 6) == 0 && !cmd->next)
		ft_unset(cmd->arg, 0, len2(cmd->arg));
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
	ft_modify_env();
	// ft_unset_old();
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
