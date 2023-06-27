/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:42 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/27 10:18:20 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Les fonctions flag_double_quotes et flag_single_quotes permettent
	de determiner si les quotes sont fermes ou non.
	si le retour = 0, alors il n'y a aucune quote
	si le retour = 1, alors la quote n'est pas fermee
	si le retour = 2, alors la quote est fermee */

int	flag_double_quotes(t_line *line)
{
	int		nb;
	int		flag;

	nb = 0;
	flag = 0;
	printf("Je rentre dans la fonction flag_double_quotes\n");
	if (!line)
		return (nb);
	while (line)
	{
		if (flag == 0 && line->dq == 1)
		{
			nb++;
			flag = 1;
		}
		if (line->dq == 2)
			nb++;
		line = line->next;
	}
	return (nb);
}

int	flag_single_quotes(t_line *line)
{
	int		nb;
	int		flag;

	nb = 0;
	flag = 0;
	printf("Je rentre dans la fonction flag_single_quotes\n");
	if (!line)
		return (nb);
	while (line)
	{
		if (flag == 0 && line->sq == 1)
		{
			nb++;
			flag = 1;
		}
		if (line->sq == 2)
			nb++;
		line = line->next;
	}
	return (nb);
}

void	find_strings(t_line *line)
{
	t_line	*tmp;
	int		sq_flag;
	int		dq_flag;

	if (!line)
		return ;
	tmp = line;
	sq_flag = flag_single_quotes(tmp);
	dq_flag = flag_double_quotes(tmp);
	printf("mon sq_flag == %d\n", sq_flag);
	printf("mon dq_flag == %d\n", dq_flag);
	if (sq_flag == 2 && dq_flag == 2)
		check_both_quotes(tmp);
	else if (sq_flag == 2)
		convert_single_quotes(tmp);
	else if (dq_flag == 2)
		convert_double_quotes(tmp);
	// else if (sq_flag == 1 || dq_flag == 1)
	// 	close_quotes(tmp);
	// check guillemets
	// check l'ordre des guillemets si plusieurs
	// 	=> des '' a l'interieur des "" n'ont aucun effet
	// check serie de mots
}
