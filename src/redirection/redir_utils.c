/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:22:30 by Bea               #+#    #+#             */
/*   Updated: 2023/09/13 18:55:06 by bebigel          ###   ########.fr       */
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

int	open_fd(t_bigshell *data, t_redir *redir)
{
	t_redir	*el;

	el = redir;
	while (el != NULL)
	{
		if (el->type == DLESS)
			redirection_here_doc(data, el);
		else if (el->type == LESS)
		{
			if (redirection_less(el) == 0)
				return (FALSE);
		}
		else if (el->type == DGREAT)
			redirection_append(el);
		else if (el->type == GREAT)
			if (redirection_great(el) == 0)
				return (FALSE);
		el = el->next;
	}
	return (TRUE);
}
