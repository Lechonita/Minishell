/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:19:29 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/14 16:47:07 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	dup_bis(int new_read, int new_write)
{
	if (dup2(new_read, STDIN_FILENO) < 0 || dup2(new_write, STDOUT_FILENO) < 0)
		return ;
}

void	no_redir_in(t_bigshell *data, int pcss)
{
	if (pcss == 0)
		dup2(data->exec->fd[0][1], STDOUT_FILENO);
	else if (pcss == data->exec->nb_cmd - 1)
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd_out);
	else
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd[pcss * 2][1]);
}

void	no_redir_out(t_bigshell *data, int pcss)
{
	if (pcss == 0)
		dup_bis(data->exec->fd_in, data->exec->fd[0][1]);
	else if (pcss == data->exec->nb_cmd - 1)
		dup2(data->exec->fd[(pcss - 1) * 2][0], STDIN_FILENO);
	else
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd[pcss * 2][1]);
}

void	no_redir_in_out(t_bigshell *data, int pcss)
{
	if (pcss == 0)
		dup2(data->exec->fd[0][1], STDOUT_FILENO);
	else if (pcss == data->exec->nb_cmd - 1)
		dup2(data->exec->fd[(pcss - 1) * 2][0], STDIN_FILENO);
	else
		dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd[pcss * 2][1]);
}

void	handle_dup(t_bigshell *data, int pcss)
{
	int	red;

	red = data->redir_or_not;
	if ((data->exec->fd_in < 3 && pcss == 0 && (red == 0 || red == 2))
		|| (data->exec->fd_out < 3 && pcss == (data->exec->nb_cmd - 1)
			&& (red == 0 || red == 1)))
		return (free_all(data), exit(EXIT_FAILURE));
	if (red == 1)
		no_redir_in(data, pcss);
	else if (red == 2)
		no_redir_out(data, pcss);
	else if (red == 3)
		no_redir_in_out(data, pcss);
	else
	{
		if (pcss == 0)
			dup_bis(data->exec->fd_in, data->exec->fd[0][1]);
		else if (pcss == data->exec->nb_cmd - 1)
			dup_bis(data->exec->fd[(pcss - 1) * 2][0], data->exec->fd_out);
		else
			dup_bis(data->exec->fd[(pcss - 1) * 2][0],
				data->exec->fd[pcss * 2][1]);
	}
}
