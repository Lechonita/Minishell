/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:21:47 by Bea               #+#    #+#             */
/*   Updated: 2023/08/22 10:45:22 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	nb_red_in_cmd(t_redir *redir, int type)
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

static int	is_redir_in_cmd(t_redir *red)
{	
	if ((nb_red_in_cmd(red, LESS) == 0 && nb_red_in_cmd(red, DLESS) == 0)
		&& (nb_red_in_cmd(red, GREAT) > 0 || nb_red_in_cmd(red, DGREAT) > 0))
		return (1);
	else if ((nb_red_in_cmd(red, LESS) > 0 || nb_red_in_cmd(red, DLESS) > 0)
		&& (nb_red_in_cmd(red, GREAT) == 0 && nb_red_in_cmd(red, DGREAT) == 0))
		return (2);
	else if (nb_red_in_cmd(red, LESS) == 0 && nb_red_in_cmd(red, DLESS) == 0
		&& nb_red_in_cmd(red, GREAT) == 0 && nb_red_in_cmd(red, DGREAT) == 0)
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
		open_fd(cmd->redir);
		cmd = cmd->next;
	}
}
