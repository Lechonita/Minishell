/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:02:22 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/11 18:30:47 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

void	align_line_index(t_bigshell *data)
{
	t_line	*tmp;
	int		i;

	tmp = data->line;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
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
	var = malloc(sizeof(char) * (get_var_len(tmp, acolade) + 1));
	if (!var)
		return (NULL);
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
