/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:34:54 by lide              #+#    #+#             */
/*   Updated: 2022/08/23 20:42:41 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	handle_1(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(1);
	}
}

void	handle_4(int sig)
{
	if (sig == SIGINT)
	{
		exit(0);
	}
}

void	sig(int i)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	if (i == 1)
	{
		sa1.sa_handler = &handle_1;
		sa1.sa_flags = SA_SIGINFO;
	}
	if (i == 2)
	{
		sa1.sa_handler = &handle_2;
		sa1.sa_flags = SA_SIGINFO;
	}
	if (i == 3)
		sa1.sa_handler = SIG_IGN;
	if (i == 4)
	{
		sa1.sa_handler = &handle_4;
		sa1.sa_flags = SA_SIGINFO;
	}
	sa2.sa_handler = SIG_IGN;
	sa2.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa1, NULL);
	sigaction(SIGQUIT, &sa2, NULL);
}
