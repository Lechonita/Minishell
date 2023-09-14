/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/14 14:01:21 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_d_here_doc(char *input, char *limiter)
{
	char	*msg;
	char	*tmp;

	if (g_global.exit_status == 130)
		return (ft_putstr_fd("\n", 1));
	free(input);
	tmp = ft_strjoin(W_HD_CTRL_D, limiter);
	msg = free_strjoin(tmp, "')\n");
	ft_putstr_fd(msg, 2);
	free(msg);
	g_global.exit_status = 0;
}

t_bigshell	*locate_shell(t_bigshell *data, int status)
{
	static t_bigshell	*shell = NULL;

	if (status)
		shell = data;
	return (shell);
}

void	ft_sig_int_hd(int sig)
{
	g_global.exit_status = 130;
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	set_signal_here_doc(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = &ft_sig_int_hd;
	sigaction(SIGINT, &act, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act_quit, NULL);
	signal(SIGTSTP, SIG_IGN);
}
