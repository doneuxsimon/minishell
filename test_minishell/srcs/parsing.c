/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/21 17:36:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"


void	ft_env()
{
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		printf("%s=%s\n", g_var->name, g_var->value);
		g_var = g_var->next;
	}
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	ft_compare_n(t_list *list)
{
	int	i;

	i = 1;
	if (!list->opt)
		return(0);
	if (list->opt[0] != '-')
		return(0);
	while (list->opt[i])
	{
		if (list->opt[i] != 'n')
			return(0);
		i++;
	}
	return(1);
}

void	ft_print_code(t_list *list, int i)
{
	int	j;

	j = 0;
	while (list->arg[i][j])
	{
		if (list->arg[i][j] == '$' && list->arg[i][j + 1] && list->arg[i][j + 1] == '?')
		{
			printf("%d", g_var->returned[0]);
			j += 2;
		}
		else 
		{
			printf("%c", list->arg[i][j]);
			j++;
		}
	}
}

void	ft_echo(t_list *list)
{
	int	i;
	int	j;
	int	x;
	int	n;
	
	i = 0;
	x = 0;
	n = ft_compare_n(list);
	while(list->arg[i])
	{
		j = 0;
		while (list->arg[i][j])
		{
			if (list->arg[i][j] == '$' && list->arg[i][j + 1] && list->arg[i][j + 1] == '?')
			{
				ft_print_code(list, i);
				x = 1;
			}
			j++;
		}
		if (x == 0)
		{
			printf("%s", list->arg[i]);
			if (list->arg[i + 1])
				printf(" ");
		}
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	ft_cd(t_list *list)
{
	chdir(list->arg[0]);
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL,  0);
	printf("%s\n", tmp);
	free(tmp);
}

void	ft_minishell(char **path, char **envp)
{
	int		pid;
	char	**cmd_args;
	int		tmp;
	char	*cmd;
	char	**tmd;

	printf("jeff\n");
	cmd_args = malloc(sizeof(char *));
	tmd = malloc(sizeof(char *) * 3);
	tmd[1] = "salut";
	tmd[0] = "bloup";
	tmd[2] = NULL;
	cmd_args[0] = NULL;
	cmd = get_cmd2(path, "open");
	envp = tmd;
	pid = fork();
	if (!pid)
	{

		printf("%s\n", cmd);
		execve("./minishell", cmd_args, envp);
	}
	else
	{
		ft_begin_var(&g_var);
		while (g_var->next && ft_strncmp(g_var->name, "SHLVL", 6) != 0)
		{
			g_var = g_var->next;
		}
		if (ft_strncmp(g_var->name, "SHLVL", 6) == 0)
		{
			tmp = ft_atoi(g_var->value);
			tmp++;
			g_var->value = ft_itoa(tmp);
		}
		dprintf(2, "%s\n", g_var->value);
		waitpid(pid, NULL, 0);
	}
}

int	verify_builtins(t_list *list, char **envp, char **path)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ft_strncmp(list->ft, "echo", 5) == 0)
	{
		ft_echo(list);
		i = 1;
	}
	if (ft_strncmp(list->ft, "cd", 3) == 0)
	{
		ft_cd(list);
		i = 1;
	}
	if (ft_strncmp(list->ft, "pwd", 4) == 0)
	{
		ft_pwd();
		i = 1;
	}
	if (ft_strncmp(list->ft, "env", 4) == 0)
	{
		ft_env();
		i = 1;
	}
	if (ft_strncmp(list->ft, "exit", 5) == 0)
	{
		ft_exit();
		i = 1;
	}
	if (ft_strncmp(list->ft, "export", 6) == 0)
	{
		ft_export(list->arg, &j, len2(list->arg));
		i = 1;
	}
	if (ft_strncmp(list->ft, "unset", 6) == 0)
	{
		ft_unset(list->arg, &j, len2(list->arg));
		i = 1;
	}
	if (ft_strncmp(list->ft, "./minishell", 12) == 0)
	{
		ft_minishell(path, envp);
		i = 1;
	}
	return (i);
}

char	*get_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*command;
	char	**cmd_paths;

	cmd_paths = ft_split(path, ':');
	while (*cmd_paths)
	{
		tmp = ft_strjoin(*cmd_paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		cmd_paths++;
	}
	return (NULL);
}
