/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:03:19 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/17 11:26:50 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

t_redir	*last_redir(t_bigshell *data, int type, int type2)
{
	int		count;
	t_redir	*lst;

	if (type == GREAT && type2 == DGREAT)
		count = count_file(data, GREAT) + count_file(data, DGREAT);
	else if (type == LESS && type2 == DLESS)
		count = count_file(data, LESS) + count_file(data, DLESS);
	lst = data->in_out;
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

char	*in_file_path(t_bigshell *data)
{
	t_token	*tok;
	t_redir	*redir_last;

	tok = data->token;
	if (data->redir_or_not == 0 || data->redir_or_not == 2)
	{
		if ((count_file(data, LESS) == 1 && data->exec->here_doc == 0)
			|| (count_file(data, LESS) == 0 && data->exec->here_doc == 1))
		{
			while (tok->next != NULL)
			{
				if ((tok->type == LESS || tok->type == DLESS)
					&& tok->next->type == WORD)
					return (tok->next->value);
				tok = tok->next;
			}		
		}
		else
		{
			redir_last = last_redir(data, LESS, DLESS);
			return (redir_last->file);
		}
	}
	return (NULL);
}

char	*out_file_path(t_bigshell *data)
{
	t_token	*tok;
	t_redir	*redir_last;

	tok = data->token;
	if (data->redir_or_not < 2)
	{
		if ((count_file(data, GREAT) == 1 && count_file(data, DGREAT) == 0)
			|| (count_file(data, GREAT) == 0 && count_file(data, DGREAT) == 1))
		{
			while (tok->next != NULL)
			{
				if ((tok->type == GREAT || tok->type == DGREAT)
					&& tok->next->type == WORD)
					return (tok->next->value);
				tok = tok->next;
			}
		}
		else
		{
			redir_last = last_redir(data, GREAT, DGREAT);
			return (redir_last->file);
		}
	}
	return (NULL);
}
