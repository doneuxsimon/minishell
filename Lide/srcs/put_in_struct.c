/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/06/23 19:52:35 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

void	put_in_g(char **str, int i, int j)
{
	int	len;
	int	ct;
	t_var *new;

	new = NULL;
	ct = -1;
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
		g_var->value[ct] = str[i][ct];
	g_var->value[ct] = '\0';
	free(str[i]);
	str[i] = NULL;
	init_var(&new);
	new->before = g_var;
	g_var->next = new;
	g_var = g_var->next;
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * (len1(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

int	check_name_env(char *str, t_var **var)
{
	int verif;

	verif = 0;
	while ((*var)->before != NULL)
		*var = (*var)->before;
	while (g_var->before != NULL)
		g_var = g_var->before;
	while ((*var)->next != NULL)
	{
		if (cmp_line(str, (*var)->name))
		{
			verif = 1;
			break;
		}
		*var = (*var)->next;
	}
		if (cmp_line(str, (*var)->name))
			verif = 1;
	while (g_var->next != NULL)
	{
		if (cmp_line(str, g_var->name))
			verif = 0;
		g_var = g_var->next;
	}
		if (cmp_line(str, g_var->name))
			verif = 0;
	return (verif);
}

void	var_to_g(t_var **var, char **str, int i)
{
	t_var	*new;
	int verif;

	new = NULL;
	init_var(&new);
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
	free(str[i]);
	str[i] = NULL;
	while ((*var)->next != NULL)
		*var = (*var)->next;
	}
}

void	ft_export(char **str, t_var **var, int *i, int len)
{
	int j;
	int equal;

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
		i++;
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

void	check_equal(char **str, t_var **var, int len)
{
	int	i;

	i = 0;
	find_esp(&i, len, str);
	while (i < len)
	{
		if (str[i])
		{
			if (!ft_strncmp(str[i], "export", 6)
				&& (!str[i - 1] || str[i - 1][0] == '&'))
				ft_export(str, var, &i, len);
			// else if (find_equal(str[i]))
		}
		else
			i++;
	}
}

void	init_var(t_var **var)
{
	(*var)->name = NULL;
	(*var)->value = NULL;
	(*var)->next = NULL;
	(*var)->before = NULL;
}

void	put_in_struct(char **str, t_list **cmd, t_var **var)
{
	int	len;
	int	i;

	i = -1;
	init_var(var);
	len = len2(str);
	check_equal(str, var, len);
	redirection(str, cmd, len);
	while (++i < len)
		printf("%s\n", str[i]);
}
