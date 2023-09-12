/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:56 by user              #+#    #+#             */
/*   Updated: 2023/09/12 16:37:03 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_execve(t_bigshell *data)
{
	if (errno == EACCES)
	{
		dprintf(2, "\033[1;31merror_execve %d - %s\033[0m\n", errno, strerror(errno));
		free_all(data);
		ft_exit(errno, strerror(errno));
		return ;
	}
	else
	{
		dprintf(2, "\033[1;31merror_execve %d - %s\033[0m\n", errno, strerror(errno));
		free_all(data);
		ft_exit(EXIT_FAILURE, W_EXECVE);
	}
}

int	msg_not_found(char *msg, char *str)
{
	char	*tmp;
	char	*line;

	dprintf(2, "\033[1;37mMSG not found \033[0m");
	tmp = ft_strjoin(msg, str);
	line = free_strjoin(tmp, "\n");
	ft_putstr_fd(line, 2);
	free(line);
	g_global.exit_status = 127;
	return (127);
}

int	is_directory(char *msg, char *str)
{
	char	*line;

	line = ft_strjoin("Minishell: ", msg);
	line = free_strjoin(line, str);
	ft_putstr_fd(line, 2);
	free(line);
	g_global.exit_status = 126;
	return (126);
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
		ft_putendl_fd(msg, 2);
	if (err_no == 13)
		g_global.exit_status = 126;
	else
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
