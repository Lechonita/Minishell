/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:56 by user              #+#    #+#             */
/*   Updated: 2023/06/26 17:00:03 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_execve(t_bigshell *data)
{
	ft_putnbr_fd(errno, 2);
	if (errno == EACCES)
		return (ft_free_all(data), ft_exit(errno, strerror(errno)));
	else
		return (ft_free_all(data), ft_exit(EXIT_FAILURE, W_EXECVE));
}

void	msg_not_found(char *msg, char *str)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(msg, str);
	line = ft_strjoin(tmp, "\n");
	ft_putstr_fd(line, 2);
	free(tmp);
	free(line);
}

void	error_not_found(t_bigshell *data, char *msg, char *str)
{
	msg_not_found(msg, str);
	ft_free_all(data);
	exit (127);
}

void	ft_exit(int err_no, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(err_no);
}