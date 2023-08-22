/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:48:37 by bebigel           #+#    #+#             */
/*   Updated: 2023/08/22 10:49:46 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redir	*last_redir_in_cmd(t_redir *redir, int type, int type2)
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

void	fd_in_file_in_cmd(t_simple_cmd *cmd)
{
	t_redir	*redir_last;

	redir_last = last_redir_in_cmd(cmd->redir, LESS, DLESS);
	if (redir_last)
	{
		cmd->fd_in = redir_last->fd;
		cmd->in_file = redir_last->file;
		close_fd_in_cmd(cmd->redir, redir_last->idx, DLESS, LESS);
	}
	return ;
}

void	fd_out_file_in_cmd(t_simple_cmd *cmd)
{
	t_redir	*redir_last;

	redir_last = last_redir_in_cmd(cmd->redir, GREAT, DGREAT);
	if (redir_last)
	{
		cmd->fd_out = redir_last->fd;
		cmd->out_file = redir_last->file;
		close_fd_in_cmd(cmd->redir, redir_last->idx, DGREAT, GREAT);
	}
	return ;
}

void	add_in_out_to_cmd(t_bigshell *data)
{
	t_simple_cmd	*cmd;

	cmd = data->simple_cmd;
	while (cmd != NULL)
	{
		fd_in_file_in_cmd(cmd);
		fd_out_file_in_cmd(cmd);
		cmd = cmd->next;
	}
}
