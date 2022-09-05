/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:48:38 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 21:49:05 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	error_init_returned(int verif)
{
	if (verif)
		free(g_var->returned);
	free(g_var);
	perror("init_returned");
	return (1);
}
