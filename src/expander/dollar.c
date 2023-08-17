/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:20:05 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/17 17:19:45 by jrouillo         ###   ########.fr       */
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
	free(var);
}

void	do_dollar_ret(t_line *line)
{
	t_line	*tmp;
	char	*ret;

	if (!line)
		return ;
	tmp = line;
	ret = ft_itoa(g_exit_status);
	tmp->c = ret[0];
	if (ret[1])
		tmp = line_add_node(tmp, ret[1], tmp->index);
	if (ft_strlen(ret) == 3 && ret[2])
	{
		tmp = tmp->next;
		tmp = line_add_node(tmp, ret[2], tmp->index);
	}
	free(ret);
}

void	find_dollar_dollar_bill(t_bigshell *data, t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	tmp = line;
	while (tmp)
	{
		if (tmp->c == '$')
		{
			if (tmp->next && tmp->next->c == '?')
				do_dollar_ret(tmp->next);
			if (!tmp->next || tmp->next->type == BLANK
				|| tmp->next->type == NEW_LINE)
				tmp->type = WORD;
			if (tmp->next && (tmp->dq == 1 || (tmp->dq == 0 && tmp->sq == 0)))
			{
				if (tmp->next->type == WORD)
					do_expansion(data, tmp, tmp->index);
			}
			else
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}
