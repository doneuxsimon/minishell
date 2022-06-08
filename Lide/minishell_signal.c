/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:12:00 by lide              #+#    #+#             */
/*   Updated: 2022/06/08 20:12:02 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	test(int sig)
{
	if (sig == SIGINT)
		sig = sig;
	if (sig == SIGQUIT)
		sig = sig;
}

int main(void)
{
	struct sigaction sa1;
	char* tmp;
	int i;

	i = 0;
	while (i++ < 10)
	{
		tmp = readline("Minishell $> ");
		add_history(tmp);
		sa1.sa_handler = &test;
		sa1.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa1, NULL);
		sigaction(SIGQUIT, &sa1, NULL);
		sigaction(4, &sa1, NULL);
		// while (1)
		// 	sleep(100);
	}
	return (0);
}
