/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/12 11:04:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/input.h"

void	ft_sig_int(int sig)
{
	g_global.exit_status = 130;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	set_signal(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = &ft_sig_int;
	sigaction(SIGINT, &act, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act_quit, NULL);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_sig_int_child(int sig)
{
	g_global.exit_status = 130;
	(void)sig;
}

void	ft_sig_quit_child(int signal)
{
	g_global.exit_status = 131;
	(void)signal;
}

void	set_signal_child(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = &ft_sig_int_child;
	sigaction(SIGINT, &act, NULL);
	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = SA_RESTART;
	act_quit.sa_handler = &ft_sig_quit_child;
	signal(SIGTSTP, SIG_IGN);
}

/*
pour le SIGINT: CTRL + C
	printf("\n");			move to the next line
	rl_on_new_line();		regenerate the prompt on a newline
	rl_replace_line("", 0); clear the previous text
	rl_redisplay();			redisplay the prompt on a newline
*/
