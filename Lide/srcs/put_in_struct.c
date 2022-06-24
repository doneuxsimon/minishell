/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/06/24 19:42:25 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	put_in_g(char **str, int i, int j)
{
	int	len;
	int	ct;
	int	x;
	t_var *new;

	new = NULL;
	ct = -1;
	x = 0;
	len = len1(str[i]);
	g_var->name =(char *)malloc(sizeof(char) * (j + 1));
	if (!g_var->name)
		printf("error malloc put in g\n");
	g_var->value =(char *)malloc(sizeof(char) * (len - j));
	if (!g_var->value)
		printf("error malloc put in g\n");
	while(++ct < j)
		g_var->name[ct] = str[i][ct];
	g_var->name[ct] = '\0';
	while(str[i][++ct])
		g_var->value[x++] = str[i][ct];
	g_var->value[x] = '\0';
	free(str[i]);
	str[i] = NULL;
	new = init_var(new);
	new->before = g_var;
	g_var->next = new;
	g_var = g_var->next;
}

int	check_name_env(char *str, t_var **var)
{
	int verif;
	int verif2;

	verif = 0;
	verif2 = 0;
	while ((*var)->before != NULL)
		*var = (*var)->before;
	while (g_var->before != NULL)
		g_var = g_var->before;
	while ((*var)->next != NULL)
	{
		if (cmp_line(str, (*var)->name))
			break ;
		*var = (*var)->next;
	}
	if (cmp_line(str, (*var)->name))
		verif = 1;
	while (g_var->next != NULL)
	{
		if (cmp_line(str, g_var->name))
			break ;
		g_var = g_var->next;
	}
	if (cmp_line(str, g_var->name))
		verif2 = 1;
	if (verif == 1 && verif2 == 1)
		return (2);
	if (verif == 1)
		return (1);
	return (0);
}

void	var_to_g(t_var **var, char **str, int i)
{
	t_var	*new;
	int verif;

	new = NULL;
	new = init_var(new);
	verif = check_name_env(str[i], var);
	if (verif == 1)
	{
		g_var->name = ft_strdup((*var)->name);
		if (!g_var->name)
			printf("error maloc var_to_g");
		g_var->value = ft_strdup((*var)->value);
		if (!g_var->value)
			printf("error maloc var_to_g");
		g_var->next = new;
		new->before = g_var;
		g_var = g_var->next;
	}
	else if (verif == 2)
	{
		free(g_var->value);
		g_var->value = ft_strdup((*var)->value);
		if (!g_var->value)
			printf("error maloc var_to_g");
	}
	while ((*var)->next != NULL)
		*var = (*var)->next;
	while (g_var->next != NULL)
		g_var = g_var->next;
	free(str[i]);
	str[i] = NULL;
}

void	ft_export(char **str, t_var **var, int *i, int len)
{
	int j;
	int equal;


	str[*i] = NULL;
	(*i)++;
	while(*i < len)
	{
		equal = 0;
		if (str[*i] && (str[*i][0] == '|' || str[*i][0] == '&'))
			break ;
		if (str[*i])
		{
			j = 0;
			while (str[*i][j] && str[*i][j] != '=')
				j++;
			if (str[*i][j])
				put_in_g(str, *i, j);
			else
				var_to_g(var, str, *i);
				//mettre egalité dans variable global
				//else if check dans var
		}
		(*i)++;
	}
}

void	find_esp(int *i, int len, char **str)
{
	int	tmp;

	tmp = *i;
	while (tmp < len)
	{
		if (str[tmp] && str[tmp][0] == '&' && !str[tmp][1])
			*i = ++tmp;
		else
			tmp++;
	}
}

int check_sep_exp(int i, int len, char **str)
{
	if (i == 0 || (i > 0 && str[i - 1][0] == '&'))
	{
		while (++i < len)
		{
			if (str[i] && str[i][0] == '|' && !str[i][1])
				return (0);
			if (str[i] && (str[i][0] == '&'
				|| (str[i][1] && str[i][1] == '|')))
				return (1);
		}
		return (1);
	}
	return (0);
}

void	ft_unset()//unset value puis utiliser unset pour supprimer les doublons dans les autres fonctions

void	check_equal(char **str, t_var **var, int len)
{
	int	i;

	i = 0;
	find_esp(&i, len, str);
	while (i < len)
	{
		if (str[i])
		{
			if (check_sep_exp(i, len, str))
			{
				if (!ft_strncmp(str[i], "export", 6))
					ft_export(str, var, &i, len);
				else if (!ft_strncmp(str[i], "unset", 5))
					ft_unset(str, var, &i, len);
			}
			else
				i++;
			// else if (find_equal(str[i]))
		}
		else
			i++;
	}
}

void	put_in_struct(char **str, t_list **cmd, t_var **var)
{
	int	len;
	int	i;

	i = -1;
	*var = init_var(*var);
	len = len2(str);
	check_equal(str, var, len);
	redirection(str, cmd, len);
	while (++i < len)
		printf("%s\n", str[i]);
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		printf("name = %s| value = %s\n", g_var->name, g_var->value);
		g_var = g_var->next;
	}
	printf("name = %s| value = %s\n", g_var->name, g_var->value);
}
