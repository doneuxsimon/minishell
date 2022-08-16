/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:43 by sdoneux           #+#    #+#             */
/*   Updated: 2022/08/16 22:45:39 by sdoneux          ###   ########.fr       */
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
	//printf("%s| value = %s\n", g_var->name, g_var->value);
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int ft_compare_n(t_list *list)
{
	int i;

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

void	ft_echo(t_list *list)
{
	int i;
	int j;
	int c;
	int d;
	int before;
	int stop;
	int after;
	int test;
	int n;
	DIR *folder;
	char *folder_name;
	struct dirent *entry;
	char *search;
	
	i = 0;
	test = 0;
	n = ft_compare_n(list);
	while(list->arg[i])
	{
		j = 0;
		while (list->arg[i][j])
		{
			if (list->arg[i][j] == '\\')
			{
				printf("%c", list->arg[i][j + 1]);
				j++;
				j++;
			}
			else if (list->arg[i][j] == '{')
			{
				before = j - 1;
				while (list->arg[i][before])
				{
					if (list->arg[i][before] == ' ')
						exit(0);
					before--;
				}
				stop = j;
				after = j;
				while (list->arg[i][after] != '}')
					after++;
				after++;
				j++;
				while(j < after - 1)
				{
					c = before;
					while (c < stop)
					{
						printf("%c", list->arg[i][c]);
						c++;
					}
					while (list->arg[i][j] != ',' && j < after - 1)
					{
						printf("%c", list->arg[i][j]);
						j++;
					}
					d = after;
					while (list->arg[i][d] && list->arg[i][d]!= ' ')
					{
						printf("%c", list->arg[i][d]);
						d++;
					}
					if (j < after - 1)
						printf(" ");
					j++;
				}
			}
			else if (list->arg[i][j] == '*')
			{
				d = 0;
				if (j == 0)
				{
					folder = opendir("./");
					folder_name = "";
				}
				else
				{
					folder_name = malloc(sizeof(char) * j + 1);
					c = 0;
					while (d < j)
					{
						folder_name[c] = list->arg[i][d];
						d++;
						c++;
					}
					folder_name[c] = '\0';
					folder = opendir((const char *)folder_name);
				}
				if (folder != NULL)
				{
					j++;
					c = j;
					while (list->arg[i][c])
						c++;
					c--;
					search = malloc(sizeof(char) * c - j + 2);
					c = 0;
					while (list->arg[i][j])
					{
						search[c] = list->arg[i][j];
						c++;
						j++;
					}
					search[c] = '\0';
					c = 0;
					while (c == 0)
					{
						entry = readdir(folder);
						if (ft_strncmp_end(entry->d_name, search, ft_strlen(search)) == 1)
						{
								printf("%s ",entry->d_name);
								c++;
						}
					}
					while ((entry=readdir(folder)))
					{
						if (ft_strncmp_end(entry->d_name, search, ft_strlen(search)) == 1)
						{
							printf("%s%s ",folder_name, entry->d_name);
							c++;
						}
					}
					if (c == 0)
						printf("%s\n", list->arg[i]);
					printf("%d\n", c);
						closedir(folder);
				}
			}
			else
			{
				printf("%c", list->arg[i][j]);
			}
			j++;
		}
		if (list->arg[i + 1])
			printf(" ");
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
	char *tmp;

	tmp = getcwd(NULL,  0);
	printf("%s\n", tmp);
	free(tmp);
}

void ft_minishell(char **envp)
{
	int pid;
	char **cmd_args;

	printf("jeff\n");
	cmd_args = malloc(sizeof(char *) * 2);
	cmd_args[0] = malloc(sizeof(char) * 9);
	cmd_args[0] = "minishell";
	cmd_args[1] = NULL;
	pid = fork();
	if (!pid)
	{
		execve(get_cmd2(envp, "open"), cmd_args, envp);
	}
	if (pid)
		waitpid(pid, NULL, 0);
}

int	verify_builtins(t_list *list, char **envp)
{
	int	i;

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
	if (ft_strncmp(list->ft, "./minishell", 12) == 0)
	{
		ft_minishell(envp);
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
