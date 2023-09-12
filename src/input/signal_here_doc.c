/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:23:53 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/11 22:42:29 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_d_here_doc(char *input, char *limiter, int count)
{
	char	*msg;
	char	*tmp;
	char	*tmp2;
	char	*nb;
	
	if (g_global.exit_status == 130)
		return (ft_putstr_fd("\n", 1));
	free(input);
	nb = ft_itoa(count + 1);
	tmp = ft_strjoin("Minishell: warning: here-document at line ", nb);
	free(nb);
	tmp2 = free_strjoin(tmp, " delimited by end-of-file (wanted `");
	tmp = free_strjoin(tmp2, limiter);
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

// void	sigint_handler_hd(int sig)
// {
// 	t_bigshell	*data;
	
// 	g_global.exit_status = 130;
// 	data = locate_shell(NULL, 0);
// 	(void)data;
// 	(void)sig;
// }

// void	set_signal_here_doc(void)
// {
// 	struct sigaction	sa_int_hd;
// 	struct sigaction	sa_quit_hd;

// 	sigemptyset(&sa_int_hd.sa_mask);
// 	sa_int_hd.sa_flags = SA_RESTART;
// 	sa_int_hd.sa_handler = &sigint_handler_hd;
// 	sigemptyset(&sa_quit_hd.sa_mask);
// 	sa_quit_hd.sa_flags = SA_RESTART;
// 	sa_quit_hd.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sa_int_hd, NULL);
// 	sigaction(SIGQUIT, &sa_quit_hd, NULL);
// 	signal(SIGTSTP, SIG_IGN);
// }

/*
void	ctrl_d_here_doc(char *input, char *limiter, int count)
{
	// char	tmp[256];

	// tmp[0] = 0;
	// if (read(STDIN_FILENO, tmp, 0) == 0)
	// {
		free(input);
		print_ctrl_d_hd(limiter, count + 1);
	// }
}
*/