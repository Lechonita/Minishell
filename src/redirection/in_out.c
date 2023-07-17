/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:51:11 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/15 18:49:41 by Bea              ###   ########.fr       */
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

static int	is_redirection(t_bigshell *data)
{	
	if ((count_file(data, LESS) == 0 && count_file(data, DLESS) == 0)
		&& (count_file(data, GREAT) > 0 || count_file(data, DGREAT) > 0))
		return (1);
	else if ((count_file(data, LESS) > 0 || count_file(data, DLESS) > 0)
		&& (count_file(data, GREAT) == 0 && count_file(data, DGREAT) == 0))
		return (2);
	else if (count_file(data, LESS) == 0 && count_file(data, DLESS) == 0
		&& count_file(data, GREAT) == 0 && count_file(data, DGREAT) == 0)
		return (3);
	else
		return (0);
}

static int	open_fd(t_bigshell *data, t_redir *redir)
{
	t_redir	*el;

	el = redir;
	while (el != NULL)
	{
		if (el->type == DLESS)
			redirection_here_doc(data, el);
		else if (el->type == LESS)
		{
			if (redirection_less(data, el) == 0)
				return (0);
		}
		else if (el->type == DGREAT)
			redirection_append(data, el);
		else if (el->type == GREAT)
			if (redirection_great(data, el) == 0)
				return (0);
		el = el->next;
	}
	return (1);
}

int	redir_job(t_bigshell *data)
{
	data->redir_or_not = is_redirection(data);
	if (data->redir_or_not < 3)
	{
		data->in_out = init_redir(data);
		if (open_fd(data, data->in_out) == 0)
			return (0);
	}
	return (1);
}
