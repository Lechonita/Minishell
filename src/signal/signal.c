/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/21 10:08:23 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
pour le SIGINT: CTRL + C
	printf("\n");			move to the next line
	rl_on_new_line();		regenerate the prompt on a newline
	rl_replace_line("", 0); clear the previous text
	rl_redisplay();			redisplay the prompt on a newline
pour le SIGQUIT: CTRL + \
	rl_on_new_line();			regenerate the prompt on a newline
	rl_replace_line("  ", 0);	clear the previous text, replace it with 2 spaces
	rl_redisplay();				redisplay the prompt on a newline
*/

void	ft_sig_handler(int sig)
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
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = &ft_sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
