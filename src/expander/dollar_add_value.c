/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_add_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:28:20 by lechon            #+#    #+#             */
/*   Updated: 2023/07/20 15:28:43 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line *line_new_var(t_line *line, t_line *after, char c, int index)
{
	t_line *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->index = index + 1;
	new->type = WORD;
	if (line)
	{
		new->dq = line->dq;
		new->sq = line->sq;
	}
	else
	{
		new->dq = 0;
		new->sq = 0;
	}
	new->c = c;
	new->next = after;
	return (new);
}

t_line *line_add_node(t_line *line, char value, int index)
{
	if (!line)
		line = line_new_var(line, NULL, value, index);
	else
	{
		while (line && line->next && line->index != index)
			line = line->next;
		line->next = line_new_var(line, line->next, value, index);
	}
	return (line);
}

t_line *line_replace_node(t_line *line, char value, int index)
{
	if (!line || !value || !index)
		return (NULL);
	line->c = value;
	line->type = WORD;
	return (line);
}
