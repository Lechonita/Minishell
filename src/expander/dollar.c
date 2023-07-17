/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:20:05 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/17 17:01:49 by jrouillo         ###   ########.fr       */
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


int	dollar_between_quotes(t_line *line, t_line *first)
{
	t_line	*tmp;

	if (!line)
		return (0);
	tmp = first;
	while (tmp)
	{
		if (tmp->next && tmp->next->next)
		{
			if ((tmp->c == 39 && tmp->next->c == '$'
					&& tmp->next->next->c == 39)
				|| (tmp->c == 34 && tmp->next->c == '$'
					&& tmp->next->next->c == 34))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	do_expansion(t_bigshell *data, t_line *line, t_line *first, int index)
{
	char	*var;
	t_line	*tmp;

	if (!line || !line->next)
		return ;
	tmp = line;
	var = get_var(tmp->next);
	if (!var)
		return (free(var));
	if (tmp->dq == 0 && tmp->sq == 0)
		dollar_expand(data, tmp, var, index);
	if (dollar_between_quotes(tmp, first) == 1)
	{
		// tmp = dollar_in_dq(tmp);
		// tmp = dollar_with_quotes_inside(tmp);
	}
}

void	find_dollar_dollar_bill(t_bigshell *data, t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	tmp = line;
	while (tmp)
	{
		// if ((tmp->c == DQUOTE || tmp->c == SQUOTE) && tmp->next->c == '$')
		// 	tmp = quote_dollar(tmp);
		if (tmp->c == '$')
		{
			if (tmp->dq == 1 || (tmp->dq == 0 && tmp->sq == 0))
				do_expansion(data, tmp, line, tmp->index);
		}
		tmp = tmp->next;
	}
}
