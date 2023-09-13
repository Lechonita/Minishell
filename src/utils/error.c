/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:56 by user              #+#    #+#             */
/*   Updated: 2023/09/13 14:22:15 by bebigel          ###   ########.fr       */
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
		ft_putstr_fd(tmp, 2);
		free(tmp);
		free_all(data);
		g_global.exit_status = 126;
		exit(g_global.exit_status);
	}
	else
	{
		free_all(data);
		ft_exit(EXIT_FAILURE, W_EXECVE);
	}
}

int	msg_not_found(char *msg, char *str)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(msg, str);
	line = free_strjoin(tmp, "\n");
	ft_putstr_fd(line, 2);
	free(line);
	g_global.exit_status = 127;
	return (g_global.exit_status);
}

int	is_directory(char *msg, char *str)
{
	char	*line;

	line = ft_strjoin("Minishell: ", msg);
	line = free_strjoin(line, str);
	ft_putstr_fd(line, 2);
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

void	ft_exit(int err_no, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	g_global.exit_status = err_no;
	exit(g_global.exit_status);
}

int	ft_error(int err_no, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	g_global.exit_status = err_no;
	return (EXIT_FAILURE);
}
