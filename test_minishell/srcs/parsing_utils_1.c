/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:25:57 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/12 17:29:29 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_modify_env(void)
{
	int		tmp;
	char	*str;

	tmp = 0;
	ft_begin_var(&g_var);
	while (g_var->next && ft_strncmp_2(g_var->name, "SHLVL", 6) != 0)
	{
		g_var = g_var->next;
	}
	if (ft_strncmp_2(g_var->name, "SHLVL", 6) == 0)
	{
		tmp = ft_atoi(g_var->value);
		tmp++;
		str = ft_itoa(tmp);
		if (str)
		{
			free(g_var->value);
			g_var->value = str;
		}
		else
		{
			perror("itoa modify env");
			exit(1);
		}
	}
}

void	ft_minishell(char **envp)
{
	char	**cmd_args;

	cmd_args = malloc(sizeof(char *));
	if (!cmd_args)
		exit(ft_exit_malloc());
	cmd_args[0] = NULL;
	envp = g_var_to_char();
	execve("./minishell", cmd_args, envp);
}

int	verify_builtins_2(t_list *list, int i)
{
	if (ft_strncmp_2(list->ft, "env", 4) == 0)
		ft_env(&i);
	if (ft_strncmp_2(list->ft, "exit", 5) == 0)
		i = 1;
	if (ft_strncmp_2(list->ft, "export", 7) == 0)
	{
		if (!list->arg[0])
		{
			ft_export_2();
		}
		i = 1;
	}
	if (ft_strncmp_2(list->ft, "unset", 6) == 0)
	{
		ft_unset(list->arg, 0, len2(list->arg));
		i = 1;
	}
	if (ft_strncmp_2(list->ft, "pwd", 4) == 0)
	{
		ft_pwd();
		i = 1;
	}
	return (i);
}

int	verify_builtins(t_list *list, char **envp)
{
	int	i;

	i = 0;
	if (ft_strncmp_2(list->ft, "echo", 5) == 0)
	{
		ft_echo(list);
		i = 1;
	}
	if (ft_strncmp_2(list->ft, "cd", 3) == 0)
		i = 1;
	if (ft_strncmp_2(list->ft, "./minishell", 12) == 0
		&& !list->next && !list->before)
	{
		ft_minishell(envp);
		i = 2;
	}
	i = verify_builtins_2(list, i);
	return (i);
}

char	*get_cmd_utils(char **cmd_paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*cmd_paths)
	{
		tmp = ft_strjoin_2(*cmd_paths, "/");
		if (!tmp)
		{
			perror("strjoin2 in get_cmd");
			return ("MALLOC ERROR");
		}
		command = ft_strjoin_2(tmp, cmd);
		if (!command)
		{
			perror("strjoin2 in get_cmd");
			free(tmp);
			return ("MALLOC ERROR");
		}
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		cmd_paths++;
	}
	return (NULL);
}
