/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/21 16:15:40 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

	// check guillemets
	// check l'ordre des guillemets si plusieurs
	// 	=> des '' a l'interieur des "" n'ont aucun effet
	// check serie de mots

int	find_last_quote(t_line *line, int type, int limiter)
{
	t_line	*tmp;
	int		i;

	if (!line)
		return (-1);
	tmp = line;
	i = 0;
	while (tmp && tmp->index <= limiter)
	{
		if (tmp->type == type)
			i = tmp->index;
		tmp = tmp->next;
	}
	return (i);
}

int	find_limiter(t_line *line)
{
	t_line	*tmp;
	int		i;

	if (!line)
		return (-1);
	tmp = line;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == NEW_LINE)
			break ;
		i = tmp->index;
		tmp = tmp->next;
	}
	return (i);
}

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
	int		last;
	t_line	*tmp;
	t_line	*prev;

	if (!line || !type)
		return ;
	tmp = line->next;
	prev = line;
	if (closing_quote_exists(tmp, type) == 1)
	{
		last = find_last_quote(tmp, type, find_limiter(tmp));
		while (tmp && tmp->index <= find_limiter(tmp))
		{
			if (tmp->type == type && tmp->index == last)
				break ;
			else if (tmp->type == type && tmp->index != last)
				tmp = line_rm_next(prev);
			else
				tmp->type = WORD;
			prev = tmp;
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
}
