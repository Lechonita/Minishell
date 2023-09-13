/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:02:22 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/13 16:40:17 by jrouillo         ###   ########.fr       */
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

int	char_ok(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || c == 95)
		return (TRUE);
	return (FALSE);
}

char	*get_var_bis(t_line *line, char *var)
{
	int		i;

	i = 0;
	while (line)
	{
		if (char_ok(line->c) == FALSE)
			break ;
		if (line->c == ' ' || line->c == '\t')
			break ;
		var[i++] = line->c;
		line = line->next;
	}
	var[i] = '\0';
	return (var);
}

int	get_var_len(t_line *line)
{
	t_line	*tmp;
	int		i;

	if (!line)
		return (0);
	tmp = line;
	i = 0;
	while (tmp)
	{
		if (char_ok(line->c) == FALSE || tmp->c == BLANK)
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

	if (!line)
		return (NULL);
	tmp = line;
	var = malloc(sizeof(char) * (get_var_len(tmp) + 1));
	if (!var)
		return (NULL);
	var = get_var_bis(tmp, var);
	return (var);
}
