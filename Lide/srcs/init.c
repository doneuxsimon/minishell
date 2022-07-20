/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:11:46 by lide              #+#    #+#             */
/*   Updated: 2022/07/20 18:09:47 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_var	*init_var(t_var *var)
{
	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
	{
		printf("error init var\n");
		return (NULL);
	}
	var->name = NULL;
	var->value = NULL;
	var->next = NULL;
	var->before = NULL;
	return (var);
}

t_list	*init_lst(t_list *cmd)
{
	cmd = (t_list *)malloc(sizeof(t_list));
	if (!cmd)
	{
		printf("error malloc init lst\n");
		return (NULL);
	}
	cmd->ft = NULL;
	cmd->opt = NULL;
	cmd->arg = NULL;
	cmd->link = NULL;
	cmd->tmp = NULL;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->pos = 0;
	cmd->next = NULL;
	cmd->before = NULL;
	return (cmd);
}
