/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:25:25 by Bea               #+#    #+#             */
/*   Updated: 2023/07/13 17:37:54 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_file(t_bigshell *data, int type)
{
	t_token	*tok;
	int		count;

	tok = data->token;
	count = 0;
	while (tok != NULL)
	{
		if (tok->type == type)
			count++;
		tok = tok->next;
	}
	return (count);
}

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
	if (data->exec->in_file == NULL)
	{
		data->exec->fd_in = 0;
		data->exec->no_redir = 1;
		return ;
	}
	if (count_file(data, LESS) == 1)
		data->exec->fd_in = data->in->fd;
	// dup2(data->exec->fd_in, data->in->fd);
	// close(data->in->fd);
	return ;
}

void	fd_out_file(t_bigshell *data)
{
	if (data->exec->out_file == NULL)
	{
		data->exec->fd_out = 0;
		data->exec->no_redir = 2 + data->exec->no_redir;
		return ;
	}
	if (count_file(data, GREAT) == 1)
		data->exec->fd_out = data->out->fd;
	// close(data->out->fd);
	// dup2(data->out->fd, data->exec->fd_out);
	return ;
}

void	init_exec(t_bigshell *data)
{
	data->exec->here_doc = count_file(data, DLESS);
	data->exec->in_file = in_file_path(data);
	data->exec->out_file = out_file_path(data);
	dprintf(2, "in  = %s\n", data->exec->in_file);
	dprintf(2, "out = %s\n", data->exec->out_file);
	fd_in_file(data);
	fd_out_file(data);
	data->exec->nb_cmd = count_cmd(data) + 1;
	data->exec->cmd = init_cmd(data);
}
