/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:47:10 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 18:50:33 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_back(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*last;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	last = (*lst);
	while (last -> next != NULL)
		last = last -> next;
	last -> next = new;
}

static t_simple_cmd	*new_lst(int index)
{
	t_simple_cmd	*new;

	new = ft_calloc(1, sizeof(t_simple_cmd));
	new -> idx = index;
	new -> next = NULL;
	return (new);
}

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*simple_cmd;
	int				index;

	index = 0;
	simple_cmd = NULL;
	while (index < g_global.nb_cmd)
	{
		if (index == 0)
			simple_cmd = new_lst(index);
		else
			add_back(&simple_cmd, new_lst(index));
		index++;
	}
	return (simple_cmd);
}

void	fd_in_file_in_cmd(t_simple_cmd *cmd)
{
	t_redir	*redir_last;

	if (cmd->in_file == NULL)
		return ;
	redir_last = last_redir_in_cmd(cmd->redir, LESS, DLESS);
	if (redir_last)
	{
		cmd->fd_in = redir_last->fd;
		close_fd_in_cmd(cmd->redir, redir_last->idx, DLESS, LESS);
	}
	return ;
}

void	fd_out_file_in_cmd(t_simple_cmd *cmd)
{
	t_redir	*redir_last;

	if (cmd->out_file == NULL)
		return ;
	redir_last = last_redir_in_cmd(cmd->redir, GREAT, DGREAT);
	if (redir_last)
	{
		cmd->fd_out = redir_last->fd;
		close_fd_in_cmd(cmd->redir, redir_last->idx, DGREAT, GREAT);
	}
	return ;
}

// void	add_cmd_to_cmd(t_bigshell *data)
// {
// 	t_token	*tok;

// 	tok = data->token;
// }

void	add_in_out_to_cmd(t_bigshell *data)
{
	t_simple_cmd	*cmd;

	cmd = data->simple_cmd;
	while (cmd != NULL)
	{
		cmd->in_file = in_file_path_in_cmd(cmd);
		cmd->out_file = out_file_path_in_cmd(cmd);
		fd_in_file_in_cmd(cmd);
		fd_out_file_in_cmd(cmd);
		cmd = cmd->next;
	}
	// add_cmd_to_cmd(data);
	print_t_token(data);
}
