/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:13:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/05 09:34:14 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

int	token_size(t_line *current)
{
	int		size;
	t_line	*el;

	size = 1;
	el = current;
	while (el->next && el->type == el->next->type)
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
	int		pos;

	if (!data || !data->line)
		return ;
	el = data->line;
	pos = -1;
	while (el != NULL)
	{
		value = token_value(el);
		token_size = ft_strlen(value);
		create_token(data, el, value, ++pos);
		while (el->next && token_size-- > 1)
			el = el->next;
		free(value);
		el = el->next;
	}
	parser_job(data);
}
