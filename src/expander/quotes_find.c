/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/22 19:05:10 by jrouillo         ###   ########.fr       */
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
	printf("===> Je rentre dans la fonction find_closing_quote\n");
	// printf("A l'entree de cette fonction, mon char est %c\n", line->c);
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

	if (!line)
		return ;
	printf("Je rentre dans la fonction convert_quotes\n");
	if (line->next)
		tmp = line->next;
	close = find_closing_quote(tmp, type);
	printf("close = %d\n", close);
	// if (close == 0)
	// 	interpret_open_quotes(tmp, type);
	printf("=====> ici, mon char est %c\n", tmp->c);
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
	printf("Je rentre dans la fonction find_quotes\n");
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
