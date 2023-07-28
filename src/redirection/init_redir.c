/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:21:47 by Bea               #+#    #+#             */
/*   Updated: 2023/07/28 18:18:27 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_file_in_cmd(t_redir *redir, int type)
{
	t_redir	*el;
	int		count;

	el = redir;
	count = 0;
	while (el != NULL)
	{
		if (el->type == type)
			count++;
		el = el->next;
	}
	return (count);
}

static int	is_redir_in_cmd(t_redir *redir)
{	
	if ((count_file_in_cmd(redir, LESS) == 0 && count_file_in_cmd(redir, DLESS) == 0)
		&& (count_file_in_cmd(redir, GREAT) > 0 || count_file_in_cmd(redir, DGREAT) > 0))
		return (1);
	else if ((count_file_in_cmd(redir, LESS) > 0 || count_file_in_cmd(redir, DLESS) > 0)
		&& (count_file_in_cmd(redir, GREAT) == 0 && count_file_in_cmd(redir, DGREAT) == 0))
		return (2);
	else if (count_file_in_cmd(redir, LESS) == 0 && count_file_in_cmd(redir, DLESS) == 0
		&& count_file_in_cmd(redir, GREAT) == 0 && count_file_in_cmd(redir, DGREAT) == 0)
		return (3);
	else
		return (0);
}

void	add_redir_to_cmd(t_bigshell *data)
{
	t_token			*tok;
	t_simple_cmd	*cmd;

	tok = data->token;
	cmd = data->simple_cmd;
	while (cmd != NULL)
	{
		cmd->redir = init_redir_in_cmd(&tok, cmd->idx);
		cmd->redir_or_not = is_redir_in_cmd(cmd->redir);
		open_fd(data, cmd->redir);
		cmd = cmd->next;
	}
}
