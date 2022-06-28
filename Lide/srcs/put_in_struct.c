/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:31:20 by lide              #+#    #+#             */
/*   Updated: 2022/06/28 18:36:28 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_g_var(char *str)
{
	int	verif;

	verif = 0;
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		if (cmp_line(str, g_var->name))
			break ;
		g_var = g_var->next;
	}
	if (cmp_line(str, g_var->name))
		return (1);
	return (0);
}

int	check_quote(char **str, int i, int j, int *len)
{
	int	ct;
	int	verif;

	verif = -1;
	ct = 0;
	if (str[i][0] == '\'' || str[i][0] == '\"')
	{
		ct++;
		verif = 0;
		(*len)--;
	}
	while ((str[i][ct] != '\'' && str[i][ct] != '\"') && ct < j)
		ct++;
	if (ct != j)
	{
		printf("export: %s: not a valid identifier\n", str[i]);
		return (-2);
	}
	return (verif);
}

int	check_name_env(char *tmp, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while(env[i][++j] != '=')
			if (tmp[j] != env[i][j])
				break ;
		if (env[i][j] == '=' && !tmp[i])
			return (i);
	}
	return (-1);
}

int	put_in_g(char **str, int i, int j)
{
	int		len;
	int		ct;
	int		x;
	int		t;
	t_var	*new;
	char	*tmp;

	len = len1(str[i]);
	ct = check_quote(str, i, j, &len);
	if (ct == -2)
		return (0);
	new = NULL;
	x = 0;
	tmp = (char *)malloc(sizeof(char) * (j - ct));
	if (!tmp)
	{
		printf("error malloc put in g\n");
		return (0);
	}
	while (++ct < j)
		tmp[x++] = str[i][ct];
	tmp[ct] = '\0';
	t = check_name_env(tmp, env)
	if (t > -1)
		change_env();//malloc tout la phrase et remplacer l'array
	t = check_g_var(tmp);
	if (t)
	{
		free(g_var->value);
		free(tmp);
	}
	g_var->value = (char *)malloc(sizeof(char) * (len - j));
	if (!g_var->value)
	{
		printf("error malloc put in g\n");
		return (0);
	}
	x = 0;
	while (++ct < len)
		g_var->value[x++] = str[i][ct];
	g_var->value[x] = '\0';
	if (t == 0)
	{
		g_var->name = tmp;
		new = init_var(new);
		new->before = g_var;
		g_var->next = new;
		g_var = g_var->next;
	}
	return (1);
}

int	ft_export(char **str, int *i, int len)
{
	int	j;
	int	verif;

	(*i)++;
	while (*i < len)
	{
		if (str[*i])
		{
			if (str[*i][0] == '|' || str[*i][0] == '&')
				break ;
			j = 0;
			while (str[*i][j] && str[*i][j] != '=')
				j++;
			if (str[*i][j])
			{
				verif = put_in_g(str, *i, j);
				if (!verif)
					return (0);
			}
		}
		(*i)++;
	}
	return (1);
}

void	find_esp(int *i, int len, char **str)
{
	int	tmp;

	tmp = *i;
	while (tmp < len)
	{
		if (str[tmp] && str[tmp][0] == '&' && !str[tmp][1])//si considerer comme error mettre lerreur ici
			*i = ++tmp;
		else
			tmp++;
	}
}

int	check_sep_exp(int i, int len, char **str)
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

int	check_equal(char **str, int len)
{
	int	i;
	int	verif;

	i = 0;
	find_esp(&i, len, str);
	while (i < len)
	{
		if (str[i])
		{
			if (check_sep_exp(i, len, str))
			{
				if (!ft_strncmp(str[i], "export", 7))
				{
					verif = ft_export(str, &i, len);
					if (!verif)
						return (0);
				}
				else if (!ft_strncmp(str[i], "unset", 6))
				{
					verif = ft_unset(str, &i, len);
					if (!verif)
						return (0);
				}
				else
					i++;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (1);
}

int	put_in_struct(char **str, t_list **cmd)
{
	int	len;
	int	i;

	i = -1;
	len = len2(str);
	if (!check_equal(str, len))
		return (0);
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
	return (1);
}
