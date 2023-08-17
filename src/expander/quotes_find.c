/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/17 17:17:32 by jrouillo         ###   ########.fr       */
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
	int		close;
	int		limiter;
	int		last;
	t_line	*tmp;

	if (line && line->next)
		tmp = line->next;
	else
		tmp = line;
	close = closing_quote_exists(tmp, type);
	// if (close == 0)
	// 	interpret_open_quotes(tmp, type);
	if (close == 1)
	{
		limiter = find_limiter(tmp);
		last = find_last_quote(tmp, type, limiter);
		while (tmp && tmp->index <= limiter)
		{
			if (tmp->type == type && tmp->index == last)
				break ;
			else if (tmp->type == type && tmp->index != last)
				tmp->type = BLANK;
			else
				tmp->type = WORD;
			tmp = tmp->next;
		}
		print_t_line(line);
		if (tmp->next)
			find_quotes(tmp->next);
	}
}

// void	convert_quotes(t_line *line, int type)
// {
// 	int		limiter;
// 	int		last;
// 	t_line	*tmp;

// 	if (line && line->next)
// 		tmp = line->next;
// 	else
// 		tmp = line;
// 	limiter = find_limiter(tmp);
// 	last = find_last_quote(tmp, type, limiter);
// 	while (tmp && tmp->index <= limiter)
// 	{
// 		if (last == 0)
// 			break ;
// 		if (tmp->type == type && tmp->index == last)
// 			break ;
// 		else if (tmp->type == type && tmp->index != last)
// 			tmp->type = BLANK;
// 		else
// 			tmp->type = WORD;
// 		tmp = tmp->next;
// 	}
// 	print_t_line(line);
// 	if (tmp->next)
// 		find_quotes(tmp->next);
// }

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
