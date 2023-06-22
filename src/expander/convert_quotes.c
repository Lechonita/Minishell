/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:55:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/22 11:50:55 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	do_both_quotes(t_line *line)
// {
	
// }

// void	close_quotes(t_line *line)
// {
	
// }

/* Dans les cas de doubles guillemets, tous les caracteres se trouvant entre les
	guillemets deviennent des caracteres de type WORD pour former
	une seule string, a l'exception du $ (expansion) qui va aller chercher une
	valeur dans l'environnement et la remplacer dans la string.*/

void	convert_double_quotes(t_line *line)
{
	int		first;

	if (!line)
		return ;
	// printf("Je rentre dans la fonction convert_double_quotes\n");
	first = 0;
	while (line)
	{
		if (line->dq == 1 && first == 0)
			first = 1;
		else if (line->dq == 1 && first == 1)
		{
			// if (line->c == "$")
			// 	do_expansion(line);
			// else
				line->type = TYPE_WORD;
		}
		line = line->next;
	}
}

/* Dans les cas de simples guillemets, tous les caracteres se trouvant entre les
	guillemets deviennent des caracteres de type WORD
	pour former une seule string.*/

void	convert_single_quotes(t_line *line)
{
	int		first;

	if (!line)
		return ;
	// printf("Je rentre dans la fonction convert_single_quotes\n");
	first = 0;
	while (line)
	{
		if (line->sq == 1 && first == 0)
			first = 1;
		else if (line->sq == 1 && first == 1)
			line->type = TYPE_WORD;
		line = line->next;
	}
}

/* Si des doubles guillemets et des simples guillemets existent dans la ligne
	de commande, alors plusieurs cas de figure existent.
	On va determiner ou chacune s'ouvre et se ferme pour savoir le comportement
	a leur donner.
	Voici tous les cas de figure de positions de guillemets lorsque nous avons
	des simples (sq) et des doubles (dq) :
	"' '" / '" "' / "' "' / '" '" / "" '' / '' ""
*/

void	check_both_quotes(t_line *line)
{
	int		start_sq;
	int		end_sq;
	int		start_dq;
	int		end_dq;
	t_line	*tmp;

	if (!line)
		return ;
	tmp = line;
	start_sq = find_start_sq(tmp);
	end_sq = find_end_sq(tmp);
	start_dq = find_start_dq(tmp);
	end_dq = find_end_dq(tmp);
	if (start_sq > end_sq || start_dq > end_dq)
		return ;
	if (start_dq < start_sq && start_dq > end_dq) // "''"
		convert_double_quotes(tmp);
	else if (start_sq < start_dq && end_sq < end_dq) // '""'
		convert_single_quotes(tmp);
	// else if ((start_dq < start_sq && end_dq < end_sq)
	// 	|| (start_sq < start_dq && end_sq < end_dq)) // "'"'ou '"'"
	// 	close_quotes(tmp);
	// else if (end_dq < start_sq || end_sq < start_dq) // "" '' ou '' ""
	// 	do_both_quotes(tmp);
}
