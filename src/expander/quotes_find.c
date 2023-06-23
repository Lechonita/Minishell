/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/23 11:42:02 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 	// check guillemets
// 	// check l'ordre des guillemets si plusieurs
// 	// 	=> des '' a l'interieur des "" n'ont aucun effet
// 	// check serie de mots
// }

int	find_closing_quote(t_line *line, int type)
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
	t_line	*tmp;

	if (line && line->next)
		tmp = line->next;
	else
		tmp = line;
	close = find_closing_quote(tmp, type);
	printf("close == %d\n", close);
	if (close == 0)
		interpret_open_quotes(tmp, type);
	if (close == 1)
	{
		while (tmp)
		{
			if (tmp->type == type)
				break ;
			// if (quote == 34 && tmp->c == "$")
			// 	tmp = do_expansion(tmp);
			else
				tmp->type = TYPE_WORD;
			tmp = tmp->next;
		}
		if (tmp->next)
			find_quotes(tmp->next);
	}
}

void	find_quotes(t_line *line)
{
	if (!line)
		return ;
	while (line)
	{
		if (line->sq == 1)
		{
			convert_quotes(line, TYPE_SINGLE_QUOTES);
			break ;
		}
		else if (line->dq == 1)
		{
			convert_quotes(line, TYPE_DOUBLE_QUOTES);
			break ;
		}
		else
			line = line->next;
	}
}
