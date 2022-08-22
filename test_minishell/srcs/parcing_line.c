/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:50 by lide              #+#    #+#             */
/*   Updated: 2022/08/22 16:48:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

//doit faire une copie de env et l'utiliser pour etre modifier dans unset et export;	V
//placer le reste des mots dans la structure	V
//segfault random hello -n ca va | hello ca va | yo -n yes cest reussi | hello -n trop fort V
//regarde comportement <<	V je pense
//gerer $? V
//gerer fd dans out/infile
//implementer export et unset	+-
//gerer les free et les messages d'erreurs	+-

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

int	check_g_var2(char *str, char *s)
{
	if (!g_var)
	{
		printf("jeff\n");
		return(0);
	}
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		if (cmp_line(str, g_var->name) && ft_strncmp(g_var->value, s, 2) == 0)
			return (1);
		g_var = g_var->next;
	}
	if (cmp_line(str, g_var->name) && ft_strncmp(g_var->value, s, 2) == 0)
		return (1);
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
