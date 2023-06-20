/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:29:56 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 15:30:04 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	g_rec_bytes = 0;

/* Check argument:
*	Check if the argument is composed only of digits and +- sign.
*	Check if the argument is an int within [INT_MIN32, INT_MAX32] range.*/

int	is_number(char *arg)
{
	int	s;

	s = 1;
	if (*arg == '+' || *arg == '-')
	{
		if (*arg == '-')
			s = 0;
		arg++;
	}
	if (!ft_isdigit(*arg))
		return (0);
	while (*arg == '0')
		arg++;
	if (ft_strlen(arg) > 10)
		return (0);
	if ((s && ft_strlen(arg) == 10
			&& ft_strncmp(arg, "2147483647", 11) > 0)
		|| (!s && ft_strlen(arg) == 10
			&& ft_strncmp(arg, "2147483648", 11) > 0))
		return (0);
	while (*arg && ft_isdigit(*arg))
		arg++;
	if (*arg != '\0')
		return (0);
	return (1);
}

void	rec_bits(int signo, siginfo_t *info, void *other)
{
	size_t	*rec;

	(void)info;
	(void)other;
	rec = &g_rec_bytes;
	(*rec)++;
	if (signo == SIGUSR2)
	{
		ft_printf("EoString signal received.\n-> Bytes recorded: [%d]\n", *rec);
		*rec = 0;
	}
}

void	send_message(int rec_pid, char *to_send)
{
	int	i;

	while (*to_send)
	{
		i = 8;
		while (--i >= 0)
		{
			if ((*to_send >> i) & 1)
				kill(rec_pid, SIGUSR1);
			else
				kill(rec_pid, SIGUSR2);
			usleep(2000);
		}
		to_send++;
	}
	while (++i < 8)
	{
		kill(rec_pid, SIGUSR2);
		usleep(2000);
	}
	return ;
}

void	reset_server(int rec_pid)
{
	ft_printf("Something went wrong Bytes recorded: [%d]\n", g_rec_bytes);
	ft_printf("Resetting server...\n");
	while (g_rec_bytes != 0)
	{
		kill(rec_pid, SIGUSR2);
		pause();
		usleep(10000);
	}
}

int	main(int ac, char **av)
{
	int					server_pid;
	struct sigaction	sa;

	if (ac != 3)
		return (ft_printf("Usage: ./client [PID] [String]\n"), EXIT_FAILURE);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &rec_bits;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (!is_number(av[1]) || ft_atoi(av[1]) < 1)
		return (ft_printf("Wrong PID format\n"), EXIT_FAILURE);
	server_pid = ft_atoi(av[1]);
	send_message(server_pid, av[2]);
	if (g_rec_bytes != 0)
		reset_server(server_pid);
}
