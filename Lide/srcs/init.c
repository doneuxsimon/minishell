/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:11:46 by lide              #+#    #+#             */
/*   Updated: 2022/08/18 20:15:44 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_var	*init_var(t_var *var)
{
	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return ((t_var *)print_str_perror("init g_var"));
	var->name = NULL;
	var->value = NULL;
	var->next = NULL;
	var->before = NULL;
	return (var);
}

t_list	*init_lst(t_list *cmd, int line)
{
	cmd = (t_list *)malloc(sizeof(t_list));
	if (!cmd)
		return ((t_list *)print_str_perror("init cmd"));
	cmd->ft = NULL;
	cmd->opt = NULL;
	cmd->arg = NULL;
	cmd->link = NULL;
	cmd->tmp = NULL;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->ct_line = line;
	cmd->pos = 0;
	cmd->next = NULL;
	cmd->before = NULL;
	return (cmd);
}
