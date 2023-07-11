/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:40:11 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/11 15:46:23 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

/* Fonction qui retourne le dernier maillon de la liste t_line. */

t_line	*line_last(t_line	*line)
{
	while (line && line->next)
		line = line->next;
	return (line);
}

/* Fonction qui ajoute un maillon a la fin de la liste t_line. */

void	line_addback(t_line *line, t_line *new)
{
	t_line	*last;

	if (!new)
		return ;
	if (!line)
	{
		line = new;
		return ;
	}
	last = line_last(line);
	last->next = new;
}

int	find_next_index(t_line *line)
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
	new->type = determine_type(c);// dans le cas ou c'est 0 ?
	new->dq = 0;
	new->sq = 0;
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
	t_line	*tmp;

	if (!data || !line)
		return ;
	i = 0;
	while (line[i])
	{
		if (i == 0)
			data->line = line_new(NULL, line[i], i);
		else
			line_addback(data->line, line_new(data->line, line[i], i));
		i++;
	}
	tmp = data->line;
	// new_var(tmp); // gestion des cmd=123 => rajouter la var dans t_env;
	flag_double_quotes(tmp);
	flag_single_quotes(tmp);
	find_quotes(tmp);
	find_dollar_dollar_bill(data, tmp);
	print_t_line(data);
}
