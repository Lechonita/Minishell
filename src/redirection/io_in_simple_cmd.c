/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_in_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:48:37 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/01 16:00:12 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*last_redir(t_redir *redir, int type, int type2)
{
	int		count;
	t_redir	*lst;

	if (type == GREAT && type2 == DGREAT)
		count = nb_red_in_cmd(redir, GREAT)
			+ nb_red_in_cmd(redir, DGREAT);
	else if (type == LESS && type2 == DLESS)
		count = nb_red_in_cmd(redir, LESS)
			+ nb_red_in_cmd(redir, DLESS);
	lst = redir;
	while (lst != NULL && count > 0)
	{
		if (lst->type == type || lst->type == type2)
			count--;
		if (count == 0 && (lst->type == type || lst->type == type2))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static void	close_fd(t_redir *redir, int idx, int type, int type2)
{
	t_redir	*el;
	int		i;

	i = 0;
	el = redir;
	while (el != NULL && i < idx)
	{
		if (el->fd && (el->type == type || el->type == type2))
			close(el->fd);
		i++;
		el = el->next;
	}
}

static void	in_file(t_simple_cmd *cmd)
{
	t_redir	*redir_last;

	redir_last = last_redir(cmd->redir, LESS, DLESS);
	if (redir_last)
	{
		cmd->fd_in = redir_last->fd;
		cmd->in_file = redir_last->file;
		close_fd(cmd->redir, redir_last->idx, DLESS, LESS);
	}
	return ;
}

static void	out_file(t_simple_cmd *cmd)
{
	t_redir	*redir_last;

	redir_last = last_redir(cmd->redir, GREAT, DGREAT);
	if (redir_last)
	{
		cmd->fd_out = redir_last->fd;
		cmd->out_file = redir_last->file;
		close_fd(cmd->redir, redir_last->idx, DGREAT, GREAT);
	}
	return ;
}

void	add_io(t_bigshell *data)
{
	t_simple_cmd	*cmd;

	cmd = data->simple_cmd;
	while (cmd != NULL)
	{
		in_file(cmd);
		out_file(cmd);
		cmd = cmd->next;
	}
}
