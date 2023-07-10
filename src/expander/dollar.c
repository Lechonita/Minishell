/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:20:05 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/10 16:58:31 by jrouillo         ###   ########.fr       */
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
	// printf("====> Ici, mon line->c = %c\n", tmp->c);
	i = 0;
	while (tmp)
	{
		if (acolade == 1 && tmp->c == '}')
		{
			i++;
			break ;
		}
		if (acolade == 0 && tmp->type == BLANK)
			break ;
		else
			i++;
		// printf("====> et apres c'est %c pour i = %d\n", tmp->c, i);
		tmp = tmp->next;
	}
	// printf("==> The length of my var = %d\n", i);
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
	// printf("La j'ai une acolade ? %d\n", acolade);
	var = malloc(sizeof(char) * (get_var_len(tmp, acolade) + 1));
	while (tmp)
	{
		if (acolade == 0 && tmp->type == BLANK)
			break ;
		if (acolade == 1 && tmp->c == '}')
		{
			var[i++] = tmp->c;
			break ;
		}
		var[i++] = tmp->c;
		tmp = tmp->next;
	}
	var[i] = '\0';
	return (var);
}

t_line	*do_expansion(t_line *line, t_line *first)
{
	char	*var;
	t_line	*tmp;

	if (!line || !line->next)
		return (NULL);
	tmp = line;
	var = get_var(tmp->next);
	printf("==> My var = %s\n", var);
	dollar_between_quotes(tmp, first); // voir si le dollar est entoure de quotes
	dollar_between_dq(tmp);
	dollar_no_quotes(tmp);
	dollar_with_quotes_inside(tmp);
	return (tmp);
}

// t_line	*quote_dollar(t_line *line)
// {
// 	t_line	*tmp;
// 	int		type;

// 	if (!line)
// 		return (NULL);
// 	tmp = line;
// 	if (tmp->c == 34)
// 		type = DQUOTE;
// 	else if (tmp->c == 39)
// 		type = SQUOTE;
// 	if (tmp->next->next && tmp->next->next->type == type)
// 		return ()
// }

void	find_dollar(t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	tmp = line;
	// printf("Je rentre dans la fonction find_dollar\n");
	while (tmp)
	{
		// if ((tmp->c == DQUOTE || tmp->c == SQUOTE) && tmp->next->c == '$')
		// 	tmp = quote_dollar(tmp);
		if (tmp->c == '$')
		{
			if (tmp->dq == 1 || (tmp->dq == 0 && tmp->sq == 0))
				tmp = do_expansion(tmp, line);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}
