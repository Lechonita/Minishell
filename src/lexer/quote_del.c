/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:33:16 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/12 18:31:27 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_word_between_quotes(t_line *line, int start, int end)
{
	t_line	*el;

	el = line;
	while (el && el->index <= start)
		el = el->next;
	while (el && el->index < end)
	{
		if (el->type != WORD || el->c == ' ')
			return (FALSE);
		el = el->next;
	}
	return (TRUE);
}

static void	flag_quote_to_remove(t_line *line, int start, int end)
{
	t_line	*el;

	el = line;
	while (el && el->index < start)
		el = el->next;
	if (el && el->index == start)
		el->quote_flag = 1;
	while (el && el->index < end)
		el = el->next;
	if (el && el->index == end)
		el->quote_flag = 1;
}

void	rm_line_el(t_line **line)
{
	t_line	*current;
	t_line	*prev;

	prev = NULL;
	current = *line;
	while (current != NULL)
	{
		if (current->quote_flag == 1 && prev == NULL)
		{
			*line = current->next;
			free(current);
			current = *line;
		}
		else if (current->quote_flag == 1 && prev != NULL)
		{
			prev->next = current->next;
			free(current);
			current = prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	delete_squotes(t_line *line)
{
	t_line	*el;
	int		start;
	int		end;

	el = line;
	if (flag_single_quotes(el) == 0)
		return ;
	while (el)
	{
		if (el->sq != 0)
		{
			start = el->index;
			while (el->sq != 2)
				el = el->next;
			end = el->index;
			if (is_word_between_quotes(line, start, end) == TRUE)
				flag_quote_to_remove(line, start, end);
		}
		if (el && el->next)
			el = el->next;
		else
			break ;
	}
}

void	delete_dquotes(t_line *line)
{
	t_line	*el;
	int		start;
	int		end;

	el = line;
	if (flag_double_quotes(el) == 0)
		return ;
	while (el)
	{
		if (el->dq != 0)
		{
			start = el->index;
			while (el->dq != 2)
				el = el->next;
			end = el->index;
			if (is_word_between_quotes(line, start, end) == TRUE)
				flag_quote_to_remove(line, start, end);
		}
		if (el && el->next)
			el = el->next;
		else
			break ;
	}
}
