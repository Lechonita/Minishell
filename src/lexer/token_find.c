/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/29 14:47:08 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	token_size(t_line *current)
{
	int 	size;
	t_line	*el;

	size = 1;
	el = current;
	while (el->next && el->type == el->next->type
			&& el->next->type != TYPE_BLANK)
	{
		size++;
		el = el->next;
	}
	return (size);
}

char	*token_value(t_line *current)
{
	t_line	*el;
	char	*value;
	int		size;
	int		i;

	i = 0;
	el = current;
	size = token_size(current);
	value = ft_calloc(sizeof(char *), size + 1);
	while (el != NULL && i < size)
	{
		value[i] = el->c;
		i++;
		el = el->next;
	}
	value[i] = '\0';
	return (value);
}

void	find_tokens(t_bigshell *data)
{
	t_line	*el;
	char	*value;
	int		token_size;
	int 	pos;

	if (!data || !data->line)
		return ;
	el = data->line;
	pos = -1;
	while (el != NULL)
	{
		value = token_value(el);
		token_size = ft_strlen(value);
		ft_create_token(data, el, value, ++pos);
		while (el->next && token_size-- > 0)
			el = el->next;
		free(value);
		el = el->next;
	}
	print_t_token(data);
}


/*
t_token	*token_last(t_token	*token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

void	token_addback(t_token *token, t_token *new)
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

Fonction qui cree un maillon t_token pour ajouter a la
	liste chainee.

t_token	*token_new(t_line *first, t_line *current, int start)
{
	t_token			*new;
	static int		i;
	int				j;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	j = 0;
	new->index = i;
	new->type = current->type;
	while (first->index != start)
		first = first->next;
	while (first->index < current->index)
	{
		new->value[j] = first->c;
		first = first->next;
		j++;
	}
	new->value[j] = '\0';
	new->next = NULL;
	i++;
	return (new);
}

void	ft_create_token(t_bigshell *data, t_line *current, int start)
{
	printf("==> Je viens creer un token\n");
	if (!data || !data->line || !current)
		return ;
	if (start == 0)
		data->token = token_new(data->line, current, start);
	else
		token_addback(data->token, token_new(data->line, current, start));
}

void	find_tokens(t_bigshell *data)
{
	int		type;
	int		start;
	t_line	*el;

	if (!data || !data->line)
		return ;
	type = 0;
	start = 0;
	el = data->line;
	while (el != NULL)
	{
		type = el->type;
		if (el->next && type != el->next->type)
		{
			// if (!special_cases(el))
		// gerer les cas speciaux = lorsqu'il y a plusieurs mots d'affiles, les guillemets, $
			if (type == TYPE_WORD && el->next->type == TYPE_BLANK
				&& el->next->next
				&& el->next->next->type == TYPE_WORD)
				continue ;
			else
			{
				ft_create_token(data, el, start);
				start = el->index;
			}
		}
		el = el->next;
	}
	print_t_token(data);
}
*/