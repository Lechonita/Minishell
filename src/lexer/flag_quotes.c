/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:37:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/10 13:42:14 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

/* Ces fonctions remplissent les valeurs t_line->sq et t_line->dq
	Elle va flagger les doubles / simplesguillemets s' il y en a.
	dq = 0 - s'il n'y a eu aucun double / simple guillemet
	dq = 1 - si les doubles / simples guillemets ont ete ouverts
	dq = 2 - si les doubles / simples guillemets ont ete fermes
	Remettre dq / sq a zero apres la fermeture du double guillemet, pour les
	prochains maillons. */

void	flag_double_quotes(t_line *line)
{
	int		dq;
	t_line	*el;

	dq = 0;
	el = line;
	while (el != NULL)
	{
		if (dq == 2)
			dq = 0;
		if (el->type == DQUOTE)
			dq++;
		el->dq = dq;
		el = el->next;
	}
}

void	flag_single_quotes(t_line *line)
{
	int		sq;
	t_line	*el;

	sq = 0;
	el = line;
	while (el != NULL)
	{
		if (sq == 2)
			sq = 0;
		if (el->type == SQUOTE)
			sq++;
		el->sq = sq;
		el = el->next;
	}
}
