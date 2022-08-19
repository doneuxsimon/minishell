/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/08/19 19:56:42 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

//doit faire une copie de env et l'utiliser pour etre modifier dans unset et export;	V
//placer le reste des mots dans la structure	V
//segfault random hello -n ca va | hello ca va | yo -n yes cest reussi | hello -n trop fort V
//regarde comportement <<	V je pense
//gerer $? V
//gerer fd dans out/infile	+-
//implementer export et unset	+-
//gerer les free et les messages d'erreurs	+-
//gere ctrl c dans <<

int	check_sep(char **str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (str[i][0] && str[i][0] == '&' && !str[i][1])
			return (0);
		else if (str[i][0] && str[i][1] && !str[i][2]
			&& ((str[i][0] == '&' && str[i][1] == '&')
			|| (str[i][0] == '|' && str[i][1] == '|')))
			return (0);
	}
	return (1);
}

char	**get_line(char *line)
{
	char	**str;
	int		len;

	str = mini_split(line);
	if (!str)
		return (NULL);
	len = len2(str);
	if (!check_sep(str, len))
	{
		printf("you can only use '|' has a separator\n");
		free_split(str, len);
		return (NULL);
	}
	str = check_dol(str, len);
	if (!str)
		return (NULL);
	return (str);
}

void	free_envp(void)
{
	t_var	*tmp;

	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		tmp = g_var;
		g_var = g_var->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(g_var->name);
	free(g_var->value);
	free(g_var);
}

int *init_returned(void)
{
	int	*i;

	i = (int *)malloc(sizeof(int));
	*i = 0;
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	char				**str;
	int					i;
	t_list				*cmd;
	static int			ct_line;

	(void)argc;
	(void)argv;
	cmd = NULL;
	i = 0;
	g_var = init_var(g_var);
	if (!g_var)
		return (1);
	g_var->returned = init_returned();
	if (!g_var->returned)
	{
		free(g_var);
		return (1);
	}
	if (ft_export(envp, &i, len2(envp)) )
	{
		free_envp();
		return (1);
	}
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
			return (0);//changer avant la fin
			// exit(0);
		}
		add_history(line);
		str = get_line(line);//si error malloc ne s'arrete pas
		if (str)
		{
			i = put_in_struct(str, &cmd);
			// if (!i)
			// 	return (1);
		}
		else
			free(cmd);
	}
	return (0);
}
