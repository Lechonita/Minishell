/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:56 by user              #+#    #+#             */
/*   Updated: 2023/09/13 15:55:23 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_execve(t_bigshell *data, char *msg)
{
	char	*tmp;

	if (errno == EACCES)
	{
		tmp = ft_strjoin("Minishell: ", msg);
		tmp = free_strjoin(tmp, ": Permission denied\n");
		ft_putstr_fd(tmp, STDERR_FILENO);
		free(tmp);
		free_all(data);
		g_global.exit_status = 126;
		exit(g_global.exit_status);
	}
	else
	{
		free_all(data);
		ft_putendl_fd(W_EXECVE, 2);
		g_global.exit_status = errno;
		exit(g_global.exit_status);
	}
}

int	msg_not_found(char *msg, char *str)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(msg, str);
	line = free_strjoin(tmp, "\n");
	ft_putstr_fd(line, STDERR_FILENO);
	free(line);
	g_global.exit_status = 127;
	return (g_global.exit_status);
}

int	is_directory(char *msg, char *str)
{
	char	*line;

	line = ft_strjoin("Minishell: ", msg);
	line = free_strjoin(line, str);
	ft_putstr_fd(line, STDERR_FILENO);
	free(line);
	g_global.exit_status = 126;
	return (g_global.exit_status);
}

void	error_not_found(t_bigshell *data, char *msg, char *str)
{
	msg_not_found(msg, str);
	free_all(data);
	g_global.exit_status = 127;
	exit(g_global.exit_status);
}

int	ft_error(int err_no, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	g_global.exit_status = err_no;
	return (EXIT_FAILURE);
}
