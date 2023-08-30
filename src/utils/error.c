/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:56 by user              #+#    #+#             */
/*   Updated: 2023/08/30 16:55:57 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_cd(char *str)
{
	char	*res;

	res = malloc(sizeof(char) * (43 + ft_strlen(str)));
	if (!res)
		return ;
	res = ft_strjoin("Minishell: cd: ", str);
	res = freejoin(res, ": No such file or directory\n");
	ft_putstr_fd(res, 2);
	free(res);
}

void	error_execve(t_bigshell *data)
{
	ft_putnbr_fd(errno, 2);
	if (errno == EACCES)
		return (free_all(data), ft_exit(errno, strerror(errno)));
	else
		return (free_all(data), ft_exit(EXIT_FAILURE, W_EXECVE));
}

int	msg_not_found(char *msg, char *str)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(msg, str);
	line = freejoin(tmp, "\n");
	ft_putstr_fd(line, 2);
	free(line);
	return (127);
}

void	error_not_found(t_bigshell *data, char *msg, char *str)
{
	msg_not_found(msg, str);
	free_all(data);
	exit(127);
}

void	ft_exit(int err_no, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(err_no);
}

int	ft_error(int err_no, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	g_global.exit_status = err_no;
	return (EXIT_FAILURE);
}
