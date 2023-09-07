/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:37:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/07 18:28:54 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

static void	rm_line_el(t_line **line, int to_remove)
{
	t_line	*el;
	t_line	*prev;

	prev = *line;
	dprintf(2, "index to remove [%d]\n", to_remove);
	if (((*line)->index) == to_remove)
	{
		el = *line;
		*line = (*line)->next;
		free(el);
		el = NULL;
		return ;
	}
	el = (*line)->next;
	while (el != NULL && el->index != to_remove)
	{
		prev = el;
		el = el->next;
	}
	if (el)
	{
		prev->next = el->next;
		free(el);
		el = NULL;
	}
	// update_idx(*line);
}

int	is_word_between_quotes(t_line *line, int start, int end)
{
	t_line	*el;

	el = line;
	while (el && el->index <= start)
		el = el->next;
	while (el && el->index < end)
	{
		if (el->type != WORD && el->type != SPACE)
			return (FALSE);
		el = el->next;
	}
	return (TRUE);
}

void	delete_quotes(t_bigshell *data, t_line *line)
{
	t_line	*el;
	int		start;
	int		end;

	el = line;
	print_t_line(data->line);
	if (flag_double_quotes(el) == 0 && flag_single_quotes(el) == 0)
		return ;
	while (el)
	{
		if (el->dq != 0)
		{
			start = el->index;
			while (el->dq != 2)
				el = el->next;
			end = el->index;
			dprintf(2, "start [%d] end [%d]\n", start, end);
			if (is_word_between_quotes(line, start, end))
			{
				rm_line_el(&line, start);
				rm_line_el(&line, end);
			}
		}
		el = el->next;
	}
	print_t_line(data->line);
}

/* Ces fonctions remplissent les valeurs t_line->sq et t_line->dq
	Elle va flagger les doubles / simplesguillemets s' il y en a.
	dq = 0 - s'il n'y a eu aucun double / simple guillemet
	dq = 1 - si les doubles / simples guillemets ont ete ouverts
	dq = 2 - si les doubles / simples guillemets ont ete fermes
	Remettre dq / sq a zero apres la fermeture du double guillemet, pour les
	prochains maillons. */

int	flag_double_quotes(t_line *line)
{
	int		dq;
	int		flag;
	t_line	*el;

	dq = 0;
	flag = 0;
	el = line;
	while (el != NULL)
	{
		if (dq == 2)
			dq = 0;
		if (el->type == DQUOTE)
		{
			dq++;
			if (dq % 2 == 0 && dq)
				flag = 1;
		}
		el->dq = dq;
		el = el->next;
	}
	return (flag);
}

int	flag_single_quotes(t_line *line)
{
	int		sq;
	int		flag;
	t_line	*el;

	sq = 0;
	flag = 0;
	el = line;
	while (el != NULL)
	{
		if (sq == 2)
			sq = 0;
		if (el->type == SQUOTE)
		{
			sq++;
			if (sq % 2 == 0 && sq)
				flag = 1;
		}
		el->sq = sq;
		el = el->next;
	}
	return (flag);
}
