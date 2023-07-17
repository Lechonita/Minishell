/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:35:49 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/14 17:08:09 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*lst_last(t_redir *lst)
{
	while (lst != NULL && lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

static void	lst_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	last = lst_last(*lst);
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

static t_redir	*new_lst(t_bigshell *data, int idx, char *type, char *file)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	new -> type = type_redir(type);
	new -> file = ft_strdup(file);
	if (new->file == NULL)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_RED_FIL), NULL);
	new -> idx = idx;
	new -> next = NULL;
	return (new);
}

t_redir	*init_redir(t_bigshell *data)
{
	t_redir		*redir;
	t_token		*el;
	int			i;

	redir = NULL;
	el = data->token;
	i = 0;
	while (el->next != NULL)
	{
		if (i == 0 && (el->type == LESS || el->type == DLESS
			|| el->type == GREAT || el->type == DGREAT))
		{
			redir = new_lst(data, i++, el->value, el->next->value);
			if (redir == NULL)
				return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_RED), NULL);
		}			
		else if (i > 0 && (el->type == LESS || el->type == DLESS
			|| el->type == GREAT || el->type == DGREAT))
			lst_add_back(&redir,
				new_lst(data, i++, el->value, el->next->value));
		el = el->next;
	}
	return (redir);
}
