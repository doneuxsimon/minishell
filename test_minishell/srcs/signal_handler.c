/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:34:54 by lide              #+#    #+#             */
/*   Updated: 2022/09/05 21:30:27 by lide             ###   ########.fr       */
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
	int	i;

	if (sig == SIGINT)
	{
		printf("\n");
		g_var->returned[0] = 130;
		i = kill(*g_var->pid, 20);
		if (i < 0)
			perror("kill didn't worked");
	}
	if (sig == SIGQUIT)
	{
		printf("Quit : 3\n");
		g_var->returned[0] = 131;
		i = kill(0, 20);
		if (i < 0)
			perror("kill didn't worked");
	}
}

void	handle_5(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		exit(0);
	}
}

void	sig(int i)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa2.sa_handler = SIG_IGN;
	sa2.sa_flags = SA_SIGINFO;
	sa1.sa_flags = SA_SIGINFO;
	if (i == 1)
		sa1.sa_handler = &handle_1;
	if (i == 2)
		sa1.sa_handler = &handle_2;
	if (i == 3)
		sa1.sa_handler = SIG_IGN;
	if (i == 4)
	{
		sa1.sa_flags = SA_NOCLDWAIT | SA_RESTART | SA_SIGINFO;
		sa2.sa_flags = SA_NOCLDWAIT | SA_RESTART | SA_SIGINFO;
		sa1.sa_handler = &handle_4;
		sa2.sa_handler = &handle_4;
	}
	if (i == 5)
		sa1.sa_handler = &handle_5;
	if (i == 5)
		sa2.sa_handler = &handle_5;
	sigaction(SIGINT, &sa1, NULL);
	sigaction(SIGQUIT, &sa2, NULL);
}
