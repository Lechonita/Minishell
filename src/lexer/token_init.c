/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:17:32 by Bea               #+#    #+#             */
/*   Updated: 2023/09/01 12:16:06 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

void	token_rm_next(t_token *tok)
{
	t_token	*tmp;

	if (!tok || !tok->next)
		return ;
	tmp = tok->next;
	tok->next = tok->next->next;
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

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
static t_token	*token_new(char *value, t_line *current_line, int idx)
{
	t_token		*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->index = idx;
	new->group = 0;
	new->type = current_line->type;
	new->aim = 0;
	new->value = ft_strdup(value);
	if (current_line->sq == 1)
		new->quote_flag = 1;
	else if (current_line->dq == 1)
		new->quote_flag = 2;
	else if (current_line->dq == 0 && current_line->sq == 0)
		new->quote_flag = 0;
	new->next = NULL;
	return (new);
}

void	create_token(t_bigshell *data, t_line *current, char *value, int pos)
{
	if (current->index == 0)
	{
		data->token = token_new(value, current, pos);
		if (!data->token)
			ft_exit(EXIT_FAILURE, W_LST_TOK);
	}
	else
		token_addback(data->token, token_new(value, current, pos));
}
