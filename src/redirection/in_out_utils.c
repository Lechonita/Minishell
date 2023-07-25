/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:35:49 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/25 17:06:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

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

static int	type_redir(char *type)
{
	if (ft_strncmp(type, ">>", 2) == 0)
		return (DGREAT);
	else if (ft_strncmp(type, "<<", 2) == 0)
		return (DLESS);
	else if (ft_strncmp(type, "<", 1) == 0)
		return (LESS);
	else if (ft_strncmp(type, ">", 1) == 0)
		return (GREAT);
	else
		return (0);
}

static t_redir	*new_lst(int idx, char *type, char *file, int pipe)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	new -> type = type_redir(type);
	new -> file = ft_strdup(file);
	if (new->file == NULL)
		return (ft_error(EXIT_FAILURE, W_LST_RED_FIL), NULL);
	new -> idx = idx;
	new -> with_cmd_nb = pipe;
	new -> next = NULL;
	return (new);
}

t_redir	*init_redir(t_bigshell *data)
{
	t_redir		*redir;
	t_token		*el;
	int			pipe;
	int			i;

	redir = NULL;
	el = data->token;
	pipe = 0;
	i = 0;
	while (el->next != NULL)
	{
		if (el->type == PIPE)
			pipe++;
		if (i == 0 && (el->type == LESS || el->type == DLESS
				|| el->type == GREAT || el->type == DGREAT))
			redir = new_lst(i++, el->value, el->next->value, pipe);
		else if (i > 0 && (el->type == LESS || el->type == DLESS
				|| el->type == GREAT || el->type == DGREAT))
			add_back(&redir, new_lst(i++, el->value, el->next->value, pipe));
		el = el->next;
	}
	return (redir);
}
