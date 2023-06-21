/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/21 12:34:53 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

/* Fonction qui cree un maillon t_token pour ajouter a la
	liste chainee. */

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

// void	find_tokens(t_bigshell *data)
// {
// 	int		type;
// 	int		start;

// 	if (!data || !data->line)
// 		return ;
// 	type = 0;
// 	start = 0;
// 	while (data->line)
// 	{
// 		type = data->line->type;
// 		if (data->line->next && type != data->line->next->type)
// 		{
// 			if (!special_cases(data->line))
// 		// gerer les cas speciaux = lorsqu'il y a plusieurs mots d'affiles, les guillemets, $
// 			if (type == TYPE_WORD && data->line->next->type == TYPE_BLANK
// 				&& data->line->next->next
// 				&& data->line->next->next->type == TYPE_WORD)
// 				continue ;
// 			else
// 			{
// 				ft_create_token(data, data->line, start);
// 				start = data->line->index;
// 			}
// 		}
// 		data->line = data->line->next;
// 	}
// 	print_t_token(data);
// }
