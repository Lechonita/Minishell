/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/11 22:44:34 by Bea              ###   ########.fr       */
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

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signal(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &ft_sig_int;
	sigaction(SIGINT, &act, NULL);
}


void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
	g_global.exit_status = 130;
}


void	set_signal_off(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/*
pour le SIGINT: CTRL + C
	printf("\n");			move to the next line
	rl_on_new_line();		regenerate the prompt on a newline
	rl_replace_line("", 0); clear the previous text
	rl_redisplay();			redisplay the prompt on a newline
*/

/*
void	ft_sig_int(int sig)
{
	g_global.exit_status = 130;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signal(void)
{
	struct sigaction	act;

	ignore_sigquit();
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = &ft_sig_int;
	sigaction(SIGINT, &act, NULL);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_sig_int_child(int sig)
{
	g_global.exit_status = 130;
	(void)sig;
}

void	set_signal_child(void)
{
	struct sigaction	act;

	ignore_sigquit();
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = &ft_sig_int_child;
	sigaction(SIGINT, &act, NULL);
	signal(SIGTSTP, SIG_IGN);
}
*/