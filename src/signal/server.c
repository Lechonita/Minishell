/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:30:13 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 15:30:16 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handler(int signo, siginfo_t *info, void *other)
{
	static char	to_print[20000];
	static char	c;
	static int	bit_no;
	static int	i;

	(void)other;
	c |= (signo == SIGUSR1);
	if (++bit_no < 8)
		c <<= 1;
	else
	{
		to_print[i++] = c;
		bit_no = 0;
		if (c == 0)
		{
			write(1, to_print, i - 1);
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
			i = 0;
			return ;
		}
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: [%d]\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("NOTE: kill this process by using 'CTRL + C', ");
	ft_printf("or 'kill -9 [PID]' in another terminal.\n");
	while (1)
		pause();
	return (0);
}
