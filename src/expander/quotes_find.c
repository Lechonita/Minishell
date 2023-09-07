/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/07 16:37:49 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

// int	find_last_quote(t_line *line, int type, int limiter)
// {
// 	t_line	*tmp;
// 	int		i;

// 	if (!line)
// 		return (-1);
// 	tmp = line;
// 	i = 0;
// 	while (tmp && tmp->index <= limiter)
// 	{
// 		if (tmp->type == type)
// 			i = tmp->index;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

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
