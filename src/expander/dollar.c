/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:20:05 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/20 17:16:18 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

/* A traiter :
	- echo "'$PATH'" ==> output la valeur de PATH, sans guillemets
	- si la valeur x ($x) n'existe pas dans t_env, alors ce n'est pas une erreur
	mais une valeur NULL. Ex : si a n'a pas ete initialise :
	echo "'$a'" ==> '' */

/* Step by step :
	1/ Je sais que je suis sur un dollar sign
	2/ Je veux regarder les caracteres qui se trouvent apres le dollar sign,
		jusqu'a la fermeture de l'acolade ou le prochain espace et je le store.
	3/ Comparer la chaine de caractere avec les names de t_env
		- Si y en a un pareil, alors rajouter data->env->value en creant un
			maillon t_line pour chaque caractere de data->env->value.
			Attention a bien retirer le $ et les acolades si y en a.
		- Si aucun name ne correspond et qu'on est dans des guillemets,
			ne rien faire.
		- Si aucun name ne correspond et qu'on n'est pas dans des guillemets,
			afficher un retour a la ligne. */

void	do_expansion(t_bigshell *data, t_line *line, int index)
{
	char	*var;
	t_line	*tmp;

	if (!line || !line->next)
		return ;
	tmp = line;
	var = get_var(tmp->next);
	if (!var)
		return (free(var));
	if ((tmp->dq == 0 && tmp->sq == 0) || tmp-> dq == 1)
	{
		dollar_expand(data, tmp, var, index);
		align_line_index(line, index);
	}
	printf("\nEn sortant ca donne ====>\n");
	print_t_line(line);
}

void	find_dollar_dollar_bill(t_bigshell *data, t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	tmp = line;
	printf("On a rien fait encore\n");
	print_t_line(line);
	while (tmp)
	{
		if (tmp->c == '$')
		{
			if (tmp->dq == 1 || (tmp->dq == 0 && tmp->sq == 0))
			{
				if (tmp->next->type == WORD)
					do_expansion(data, tmp, tmp->index);
			}
		}
		tmp = tmp->next;
	}
}
