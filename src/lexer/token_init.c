/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:17:32 by Bea               #+#    #+#             */
/*   Updated: 2023/06/29 16:00:13 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*token_last(t_token	*token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

static void	token_addback(t_token *token, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!token)
	{
		token = new;
		return ;
	}
	last = token_last(token);
	last->next = new;
}

/* Fonction qui cree un maillon t_token pour ajouter a la
	liste chainee. */

static t_token	*token_new(char *value, int type, int idx)
{
	t_token		*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->index = idx;
	new->type = type;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_create_token(t_bigshell *data, t_line *current, char *value, int pos)
{
	if (current->index == 0)
	{
		data->token = token_new(value, current->type, pos);
		if (!data->token)
			ft_exit(EXIT_FAILURE, W_LST_TOK);
	}
	else
		token_addback(data->token, token_new(value, current->type, pos));
}