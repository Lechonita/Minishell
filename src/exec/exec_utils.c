/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:00:06 by Bea               #+#    #+#             */
/*   Updated: 2023/07/17 17:45:09 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_fd(t_bigshell *data, int idx, int type, int type2)
{
	t_redir	*el;
	int		i;

	i = 0;
	el = data->in_out;
	while (el != NULL && i < idx)
	{
		if (el->fd && (el->type == type || el->type == type2))
			close(el->fd);
		i++;
		el = el->next;
	}
}

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
