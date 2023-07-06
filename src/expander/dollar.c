/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:20:05 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/06 14:45:35 by jrouillo         ###   ########.fr       */
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

int	get_var_len(t_line *line, int acolade)
{
	t_line	*tmp;
	int		i;

	if (!line)
		return (0);
	tmp = line;
	i = 1;
	while (tmp)
	{
		if ((acolade == 1 && tmp->c != '}')
			|| (acolade == 0 && tmp->type != BLANK))
			i++;
		tmp = tmp->next;
	}
	printf("==> The length of my var = %d\n", i);
	return (i);
}

char	*get_var(t_line *line)
{
	t_line	*tmp;
	char	*var;
	int		acolade;
	int		i;

	if (!line || !line->next)
		return (NULL);
	tmp = line;
	acolade = 0;
	i = 0;
	if (tmp->c == '{')
		acolade = 1;
	printf("La j'ai une adolade ? %d\n", acolade);
	var = malloc(sizeof(char) * (get_var_len(tmp, acolade) + 1));
	while (tmp)
	{
		if ((acolade == 1 && tmp->c != '}')
			|| (acolade == 0 && tmp->type != BLANK))
			var[i++] = tmp->c;
		tmp = tmp->next;
	}
	var[i] = '\0';
	return (var);
}

t_line	*do_expansion(t_line *line)
{
	char	*var;
	t_line	*tmp;

	if (!line || !line->next)
		return (NULL);
	tmp = line;
	var = get_var(tmp->next);
	printf("==> My var = %s\n", var);
	return (tmp);
}
