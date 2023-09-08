/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:37:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/08 15:29:39 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	closing_quote_exists(t_line *line, int type)
{
	if (!line || !type)
		return (-1);
	while (line)
	{
		if (line->type == type)
			return (1);
		line = line->next;
	}
	return (0);
}

void	convert_quotes(t_line *line, int type)
{
	t_line	*tmp;

	if (!line || !type)
		return ;
	tmp = line->next;
	if (closing_quote_exists(tmp, type) == 1)
	{
		while (tmp)
		{
			if (tmp->type == type)
				break ;
			else
				tmp->type = WORD;
			tmp = tmp->next;
		}
		if (tmp && tmp->next)
			find_quotes(tmp->next);
	}
}

void	find_quotes(t_line *line)
{
	t_line	*el;

	if (!line)
		return ;
	el = line;
	while (el != NULL)
	{
		if (el->sq == 1)
		{
			convert_quotes(el, SQUOTE);
			break ;
		}
		else if (el->dq == 1)
		{
			convert_quotes(el, DQUOTE);
			break ;
		}
		else
			el = el->next;
	}
	align_line_index(line, 0);
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
