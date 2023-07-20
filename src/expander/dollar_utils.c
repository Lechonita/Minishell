/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:02:22 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/20 17:27:55 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

void	align_line_index(t_line *line, int index)
{
	t_line	*tmp;
	int		i;

	if (!line)
		return ;
	tmp = line;
	i = index;
	while (tmp && tmp->index != i)
		tmp = tmp->next;
	while (tmp)
	{
		tmp->index = i++;
		tmp = tmp->next;	
	}
}

int	get_var_len(t_line *line, int acolade)
{
	t_line	*tmp;
	int		i;

	if (!line)
		return (0);
	tmp = line;
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
		tmp = tmp->next;
	}
	return (i);
}

char	*get_var_bis(t_line *line, char *var, int acolade)
{
	int		i;

	i = 0;
	while (line)
	{
		// printf("A ce moment la mon line c'est %c et son type %d\n", line->c, line->type);
		if (line->c == 34)
			break ;
		if (acolade == 0 && (line->c == ' ' || line->c == '\t'))
			break ;
		if (acolade == 1 && line->c == '}')
		{
			var[i++] = line->c;
			break ;
		}
		var[i++] = line->c;
		line = line->next;
	}
	var[i] = '\0';
	return (var);
}

int	find_closing_bracket(t_line *line)
{
	t_line	*tmp;

	// printf("Je ne pense pas rentrer ici\n");
	if (!line)
		return (1);
	tmp = line;
	while (tmp)
	{
		if (tmp->c == '}')
			return (0);
		tmp = tmp->next;
	}
	return (1);
		
}

char	*get_var(t_line *line)
{
	t_line	*tmp;
	char	*var;
	int		acolade;

	if (!line || !line->next)
		return (NULL);
	tmp = line;
	acolade = 0;
	if (tmp->c == '{')
	{
		if (find_closing_bracket(tmp) == 1)
			return (NULL);
		acolade = 1;
	}
	var = malloc(sizeof(char) * (get_var_len(tmp, acolade) + 1));
	if (!var)
		return (NULL);
	var = get_var_bis(tmp, var, acolade);
	// printf("Des le debut mon var est -%s-\n", var);
	return (var);
}
