/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:40:11 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/08 15:32:06 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_idx(t_line *line)
{
	int		i;
	t_line	*el;

	i = 0;
	el = line;
	while (el)
	{
		el->index = i++;
		el = el->next;
	}
	flag_double_quotes(line);
	flag_single_quotes(line);
	find_quotes(line);
}

static void	line_addback(t_line **line, t_line *new)
{
	t_line	*last;

	if (!new)
		return ;
	if (!*line || !line)
	{
		*line = new;
		return ;
	}
	last = (*line);
	while (last->next)
		last = last->next;
	last->next = new;
}

static int	find_next_index(t_line *line)
{
	while (line && line->next)
		line = line->next;
	return (line->index);
}

/* Fonction qui cree un maillon t_line pour ajouter a la
	liste chainee. */

t_line	*line_new(t_line *line, char c, int i)
{
	t_line	*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	if (i == -1 && line)
		i = find_next_index(line) + 1;
	new->index = i;
	new->type = determine_type(c);
	new->dq = 0;
	new->sq = 0;
	new->quote_flag = 0;
	new->c = c;
	new->next = NULL;
	return (new);
}

/* Creation des maillons de la structure t_line.
	1 caractere de la ligne de commande = 1 maillon.
	L'idee est de les typer un par un pour ensuite revenir les combiner
	en tokens. */

void	init_line(t_bigshell *data, char *line)
{
	int		i;
	t_line	*new;

	if (!data || !line)
		return ;
	i = 0;
	while (line[i])
	{
		new = line_new(data->line, line[i], i);
		if (!new)
			ft_exit(EXIT_FAILURE, W_LST_LINE);
		line_addback(&data->line, new);
		i++;
	}
	flag_double_quotes(data->line);
	flag_single_quotes(data->line);
	find_quotes(data->line);
	find_dollar_dollar_bill(data, data->line);
	check_for_export(data, data->line, line);
	delete_squotes(data->line);
	delete_dquotes(data->line);
	rm_line_el(&data->line);
	update_idx(data->line);
}
