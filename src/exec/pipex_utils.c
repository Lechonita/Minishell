/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:00:06 by Bea               #+#    #+#             */
/*   Updated: 2023/06/26 17:39:35 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_pipe(t_bigshell *data)
{
	int	i;

	i = 0;
	while (i < data->exec->nb_cmd - 1)
	{
		if (pipe(data->exec->fd[2 * i]) == -1)
			return (ft_free_all(data), ft_exit(errno, strerror(errno)));
		i++;
	}
}

void	close_pipe(t_bigshell *data)
{
	int	i;

	i = 0;
	while (i < data->exec->nb_cmd - 1)
	{
		close(data->exec->fd[2 * i][0]);
		close(data->exec->fd[2 * i][1]);
		i++;
	}
	if (data->exec->fd_in)
		close(data->exec->fd_in);
	if (data->exec->fd_out)
		close(data->exec->fd_out);
}

static void	dup_bis(int new_read, int new_write)
{
	if (dup2(new_read, STDIN_FILENO) < 0 || dup2(new_write, STDOUT_FILENO) < 0)
		return ;
}

void	handle_dup(t_bigshell *data, int pcss)
{
	if (pcss == 0)
		dup_bis(data->exec->fd_in, data->exec->fd[0][1]);
	else if (pcss == data->exec->nb_cmd - 1)
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd_out);
	else
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd[pcss * 2][1]);
	if ((data->exec->fd_in < 3 && pcss == 0)
		|| (data->exec->fd_out < 3 && pcss == data->exec->nb_cmd - 1))
		return (ft_free_all(data), exit(EXIT_FAILURE));
}
