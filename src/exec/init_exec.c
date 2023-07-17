/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:25:25 by Bea               #+#    #+#             */
/*   Updated: 2023/07/17 18:07:14 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* compte le nombre de pipe donc de processus */
int	count_cmd(t_bigshell *data)
{
	int		count;
	t_token	*el;

	count = 0;
	el = data->token;
	while (el != NULL)
	{
		if (el->type == PIPE)
			count++;
		el = el->next;
	}
	return (count);
}

void	fd_in_file(t_bigshell *data)
{
	t_redir	*redir_last;

	if (data->exec->in_file == NULL)
		return ;
	redir_last = last_redir(data, LESS, DLESS);
	data->exec->fd_in = redir_last->fd;
	close_fd(data, redir_last->idx, DLESS, LESS);
	return ;
}

void	fd_out_file(t_bigshell *data)
{
	t_redir	*redir_last;

	if (data->exec->out_file == NULL)
		return ;
	redir_last = last_redir(data, GREAT, DGREAT);
	data->exec->fd_out = redir_last->fd;
	close_fd(data, redir_last->idx, DGREAT, GREAT);
	return ;
}

void	init_exec(t_bigshell *data)
{
	print_redir(data);
	data->exec->here_doc = count_file(data, DLESS);
	data->exec->in_file = in_file_path(data);
	data->exec->out_file = out_file_path(data);
	fd_in_file(data);
	fd_out_file(data);
	data->exec->nb_cmd = count_cmd(data) + 1;
	data->exec->cmd = init_cmd(data);
	print_exec(data);
}

/*
void	fd_out_file(t_bigshell *data)
{
	t_redir	*redir_last;
	t_redir	*el;

	if (data->exec->out_file == NULL)
		return ;
	el = data->in_out;
	if ((count_file(data, GREAT) == 1 && count_file(data, DGREAT) == 0)
		|| (count_file(data, GREAT) == 0 && count_file(data, DGREAT) == 1))
	{
		while (el)
		{
			if (el->type == GREAT || el->type == DGREAT)
				data->exec->fd_out = el->fd;
			el = el->next;
		}
	}
	else
	{
		redir_last = last_redir(data, GREAT, DGREAT);
		data->exec->fd_out = redir_last->fd;
		close_fd(data, redir_last->idx, DGREAT, GREAT);
	}
	return ;
}
*/