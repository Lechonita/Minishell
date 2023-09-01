/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:20:05 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/01 11:14:19 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

/* A traiter :
	- echo "'$PATH'" ==> output la valeur de PATH, sans guillemets
	- si la valeur x ($x) n'existe pas dans t_env, alors ce n'est pas une erreur
	mais une valeur NULL. Ex : si a n'a pas été initialisé :
	echo "'$a'" ==> '' */

/* Step by step :
	1/ Je sais que je suis sur un dollar sign
	2/ Je veux regarder les caractères qui se trouvent apres le dollar sign,
		jusqu'au prochain espace / newline et je le store.
	3/ Comparer la chaîne de caractères avec les names de t_env
		- Si y en a un pareil, alors rajouter data->env->value en créant un
			maillon t_line pour chaque caractere de data->env->value.
			Attention a bien retirer le $.
		- Si aucun name ne correspond, afficher un retour a la ligne. */

int	single_quote_position(t_line *line)
{
	t_line	*tmp;

	if (!line)
		return (0);
	tmp = line;
	if (tmp->sq == 1)
	{
		while (tmp)
		{
			if (tmp->type != WORD)
				return (tmp->type);
			tmp = tmp->next;
		}
	}
	return (0);
}

void	do_dollar_ret(t_line *line)
{
	t_line	*tmp;
	char	*ret;

	if (!line)
		return ;
	tmp = line;
	ret = ft_itoa(g_global.exit_status);
	tmp->c = ret[0];
	tmp->type = WORD;
	tmp = line_rm_next(tmp);
	if (ret[1])
		tmp = line_add_node(tmp, ret[1], tmp->index);
	if (ft_strlen(ret) == 3 && ret[2])
	{
		tmp = tmp->next;
		tmp = line_add_node(tmp, ret[2], tmp->index);
	}
	free(ret);
}

t_line	*do_expansion(t_bigshell *data, t_line *line, int index)
{
	char	*var;
	t_line	*tmp;

	if (!line || !line->next)
		return (NULL);
	tmp = line;
	var = get_var(tmp->next);
	if (!var)
		return (free(var), NULL);
	if (line->next->c == '?')
		do_dollar_ret(tmp);
	else if (is_blank(line->next->c) > 0)
		tmp = line;
	else if ((tmp->dq == 0 && tmp->sq == 0)
		|| (tmp-> dq == 1 && tmp->sq == 0)
		|| (tmp->sq == 1 && single_quote_position(tmp) == DQUOTE))
		tmp = compare_var(data, tmp, var, index);
	return (free(var), tmp);
}

int	is_between_quotes(t_bigshell *data, t_line *line)
{
	t_line	*tmp;
	t_line	*prev;

	if (!line)
		return (0);
	tmp = line;
	prev = find_prev(data, tmp->index);
	if (prev && prev->type == DQUOTE && tmp->next->type == DQUOTE)
	{
		tmp->type = WORD;
		return (1);
	}
	return (0);
}

void	find_dollar_dollar_bill(t_bigshell *data, t_line *line)
{
	t_line	*tmp;
	int		flag;

	if (!data || !line)
		return ;
	tmp = line;
	flag = 0;
	while (tmp)
	{
		if (tmp->c == '$')
		{
			if (tmp->sq == 1 || !tmp->next || tmp->next->type == BLANK
				|| tmp->next->type == NEW_LINE || tmp->next->type == SQUOTE
				|| tmp->next->type == DQUOTE)
				tmp->type = WORD;
			flag = is_between_quotes(data, tmp);
			if (flag == 0 && tmp->next && tmp->next->type == WORD
				&& (tmp->dq == 1 || (tmp->dq == 0 && tmp->sq == 0)))
				tmp = do_expansion(data, tmp, tmp->index);
		}
		flag = 0;
		tmp = tmp->next;
	}
}
