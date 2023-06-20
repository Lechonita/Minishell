/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:37:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/20 15:11:55 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonction qui va permettre de determiner si les guillements sont bien
	fermes ou non. */

int	treat_as_quotes(t_line	*line)
{
	while (line)
	{
		if (line->dq == 2)
			return (1);
		line = line->next;
	}
	return (0);
}

/* Fonction qui va flagger les double guillemets s' il y en a.
	dq = 0 - s'il n'y a eu aucun double guillemet
	dq = 1 - si les double guillemets ont ete ouverts
	dq = 2 - si les double guillemets ont ete fermes
	Remettre dq a zero apres la fermeture du double guillemet, pour les
	prochains maillons. */

void	find_double_quotes(t_line *line)
{
	int		dq;

	dq = 0;
	while (line)
	{
		if (dq == 2)
			dq = 0;
		if (line->type == TYPE_DOUBLE_QUOTES)
			dq++;
		line->dq = dq;
		line = line->next;
	}
}

/* Idem que la fonction find_double_quotes mais pour des single quotes. */

void	find_single_quotes(t_line *line)
{
	int		sq;

	sq = 0;
	while (line)
	{
		if (sq == 2)
			sq = 0;
		if (line->type == TYPE_SINGLE_QUOTES)
			sq++;
		line->sq = sq;
		line = line->next;
	}
}
