/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/16 17:53:26 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/input.h"

void	print_ctrl_d_hd(char *limiter, int count)
{
	char	*msg;
	char	*tmp;
	char	*tmp2;
	char	*nb;

	nb = ft_itoa(count);
	tmp = ft_strjoin("bash: warning: here-document at line ", nb);
	tmp2 = ft_strjoin(tmp, " delimited by end-of-file (wanted `");
	free(tmp);
	tmp = ft_strjoin(tmp2, limiter);
	msg = ft_strjoin(tmp, "')\n");
	ft_putstr_fd(msg, 2);
	free(tmp);
	free(tmp2);
	free(nb);
	free(msg);
}

void	ctrl_d_here_doc(char *input, char *limiter, int count)
{
	char	tmp[256];

	tmp[0] = 0;
	if (read(STDIN_FILENO, tmp, 0) == 0)
	{
		free(input);
		print_ctrl_d_hd(limiter, count + 1);
	}
}

void	ctrl_c_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(130);
	}
}

void	set_signal_here_doc(void)
{
	struct sigaction	sa_int_hd;
	struct sigaction	sa_quit_hd;

	sigemptyset(&sa_int_hd.sa_mask);
	sa_int_hd.sa_flags = SA_RESTART;
	sa_int_hd.sa_handler = &ctrl_c_here_doc;
	sigemptyset(&sa_quit_hd.sa_mask);
	sa_quit_hd.sa_flags = SA_RESTART;
	sa_quit_hd.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int_hd, NULL);
	sigaction(SIGQUIT, &sa_quit_hd, NULL);
}
