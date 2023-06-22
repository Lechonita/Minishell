/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/22 18:07:18 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 	// check guillemets
// 	// check l'ordre des guillemets si plusieurs
// 	// 	=> des '' a l'interieur des "" n'ont aucun effet
// 	// check serie de mots
// }

int	find_closing_quote(t_line *line, char quote)
{
	if (!line || !quote)
		return (-1);
	while (line)
	{
		if (line->c == quote)
			return (1);
		line = line->next;
	}
	return (0);
}

void	convert_quotes(t_line *line, char quote)
{
	int		close;
	t_line	*tmp;

	if (!line)
		return ;
	tmp = line;
	close = find_closing_quote(tmp, quote);
	// if (close == 0)
	// 	interpret_open_quotes(tmp, quote);
	if (close == 1)
	{
		while (line)
		{
			if (line->c == quote)
				break ;
			// if (quote == 34 && line->c == "$")
			// 	line = do_expansion(line);
			// else
				line->type = TYPE_WORD;
			line = line->next;
		}
		if (line->next)
			find_quotes(line->next);
	}
}

void	find_quotes(t_line *line)
{
	if (!line)
		return ;
	while (line)
	{
		if (line->sq == 1 || line->dq == 1)
			convert_quotes(line, line->c);
		else
			line = line->next;
	}
}
