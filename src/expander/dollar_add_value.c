/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_add_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:28:20 by lechon            #+#    #+#             */
/*   Updated: 2023/09/15 14:56:06 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line	*line_new_var(t_line *line, t_line *after, char c, int index)
{
	t_line	*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->index = index;
	new->type = WORD;
	if (line)
	{
		new->dq = line->dq;
		new->sq = line->sq;
	}
	else
	{
		new->dq = 0;
		new->sq = 0;
	}
	new->c = c;
	new->quote_flag = 0;
	new->next = after;
	return (new);
}

t_line	*line_add_node(t_line *line, char value, int index)
{
	while (line && line->next && line->index != index)
		line = line->next;
	line->next = line_new_var(line, line->next, value, index);
	return (line);
}

t_line	*line_replace_node(t_line *line, char value)
{
	if (!line || !value)
		return (NULL);
	line->c = value;
	line->type = WORD;
	return (line);
}

void	line_addmiddle(t_line *line, char c, int index)
{
	t_line	*last;

	if (!line)
		return ;
	last = line;
	if (index == last->index)
		last = line_new_var(last, last->next, c, index);
	else
	{
		while (last && last->index != index - 1)
			last = last->next;
		last->next = line_new_var(last, last->next, c, index);
	}
}

t_line	*add_var(t_line *line, char *value, char *var)
{
	t_line	*tmp;
	int		idx;
	int		i;
	int		j;

	if (!line || !value || !var)
		return (NULL);
	tmp = line;
	idx = tmp->index - 1;
	i = -1;
	j = 0;
	while (value[++i])
	{
		if ((var[j] && tmp && tmp->c == var[j]))
		{
			tmp = line_replace_node(tmp, value[i]);
			tmp = tmp->next;
			j++;
		}
		else
			line_addmiddle(line, value[i], idx + 1);
		idx++;
	}
	remove_rest(tmp, ft_strlen(value), ft_strlen(var));
	return (line->next);
}
