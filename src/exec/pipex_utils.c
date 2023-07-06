/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:00:06 by Bea               #+#    #+#             */
/*   Updated: 2023/07/06 17:31:13 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

void	open_pipe(t_bigshell *data)
{
	int	i;

	i = 0;
	while (i < data->exec->nb_cmd - 1)
	{
		if (pipe(data->exec->fd[2 * i]) == -1)
			return (free_all(data), ft_exit(errno, strerror(errno)));
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



/*
void	handle_dup(t_bigshell *data, int pcss)
{
	int	red;

	red = data->exec->no_redir;
	dprintf(2, "no redirect = %d\n", red);
	if ((data->exec->fd_in < 3 && pcss == 0 && (red == 0 || red == 2))
		|| (data->exec->fd_out < 3 && pcss == (data->exec->nb_cmd - 1)
			&& (red == 0 || red == 1)))
		return (free_all(data), exit(EXIT_FAILURE));
	if (pcss == 0)
	{
		if (red == 0)
			dup_bis(data->exec->fd_in, data->exec->fd[0][1]);
		else if (red == 1 || red == 3)
			dup2(data->exec->fd[1][0], STDIN_FILENO);
	}
	else if (pcss == data->exec->nb_cmd - 1)
	{
		if (red == 0)
			dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd_out);
		else if (red == 2 || red == 3)
			dup2(data->exec->fd[(pcss - 1) * 2][1], STDOUT_FILENO);
	}
	else
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd[pcss * 2][1]);
}

*/