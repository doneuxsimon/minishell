/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:37:09 by sdoneux           #+#    #+#             */
/*   Updated: 2022/09/13 15:40:08 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	check_in_outfile2(t_list *list)
{
	sig(5);
	if (list->infile)
		dup0(list, 0);
	if (list->outfile)
		dup1(list, 0);
}
