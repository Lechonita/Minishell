/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/21 17:01:57 by bebigel          ###   ########.fr       */
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

void	ft_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = &ft_sig_int;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
