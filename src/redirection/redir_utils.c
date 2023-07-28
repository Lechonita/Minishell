/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:22:30 by Bea               #+#    #+#             */
/*   Updated: 2023/07/28 16:23:36 by Bea              ###   ########.fr       */
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

static t_redir	*new_lst(int idx, char *type, char *file)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	new -> type = type_redir(type);
	new -> file = ft_strdup(file);
	if (new->file == NULL)
		return (ft_error(EXIT_FAILURE, W_LST_RED_FIL), NULL);
	new -> idx = idx;
	new -> with_cmd_nb = idx;
	new -> next = NULL;
	return (new);
}

t_redir	*init_redir_in_cmd(t_token **token, int grp)
{
	t_redir		*redir;
	t_token		*el;
	int			i;

	redir = NULL;
	el = *token;
	i = 0;
	while (el != NULL)
	{
		if (i == 0 && (el->type == LESS || el->type == DLESS
				|| el->type == GREAT || el->type == DGREAT) && el->group == grp)
			redir = new_lst(i++, el->value, el->next->value);
		else if (i > 0 && (el->type == LESS || el->type == DLESS
				|| el->type == GREAT || el->type == DGREAT) && el->group == grp)
			add_back(&redir, new_lst(i++, el->value, el->next->value));
		else if (el->group != grp)
			el = el->next;
		el = el->next;
	}
	return (redir);
}
