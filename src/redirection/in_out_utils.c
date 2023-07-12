/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:35:49 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/11 14:37:58 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*new_lst(t_bigshell *data, int idx, char *type, char *file)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	new -> type = ft_strdup(type);
	if (new->type == NULL)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_RED_TYP), NULL);
	new -> file = ft_strdup(file);
	if (new->file == NULL)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_RED_FIL), NULL);
	new -> idx = idx;
	new -> next = NULL;
	return (new);
}

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

t_redir	*init_redir(t_bigshell *data, int type)
{
	t_redir		*redir;
	t_token		*el;
	int			i;

	redir = NULL;
	el = data->token;
	i = 0;
	while (el->next != NULL)
	{
		if (i == 0 && el->type == type)
		{
			redir = new_lst(data, i++, el->value, el->next->value);
			if (redir == NULL)
				return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_RED), NULL);
		}			
		else if (i > 0 && el->type == type)
			lst_add_back(&redir,
				new_lst(data, i++, el->value, el->next->value));
		el = el->next;
	}
	return (redir);
}
