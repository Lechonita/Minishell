/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_add_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:28:20 by lechon            #+#    #+#             */
/*   Updated: 2023/07/24 10:43:49 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

t_line *line_new_var(t_line *line, t_line *after, char c, int index)
{
	t_line *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
    printf("On va regarder ici aussi alors line new var :\n");
    // print_t_line(line);
	new->index = index + 1;
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
	new->next = after;
	return (new);
}

t_line *line_add_node(t_line *line, char value, int index)
{
    printf("Mon index la cest %d et mon line cest %c\n", index, line->c);
    printf("Pour l'instant j'ai ===>\n");
    // print_t_line(line);
    
	/*************** Normalement plus besoin ******************/
    // if (!line)
    // {
    //     printf("Estce que mon line est NULL ? oui\n");
	// 	line = line_new_var(line, NULL, value, index);
    // }
	// else
	// {
    /*****************************************************/
    
		while (line && line->next && line->index != index)
			line = line->next;
        printf("Et apres la boucle, mon t line c'est :\n");
        // print_t_line(line);
    // if (line)
		line->next = line_new_var(line, line->next, value, index);
	// }
    printf("On le perd la ?\n");
    // print_t_line(line);
	return (line);
}

t_line *line_replace_node(t_line *line, char value, int index)
{
	if (!line || !value || !index)
		return (NULL);
	line->c = value;
	line->type = WORD;
	return (line);
}

void add_var(t_line *line, char *value, int idx, char *var)
{
	t_line *tmp;
	int index;
	int i;
	int j;

	if (!line || !value || !idx || !var)
		return;
	tmp = line->next;
	index = idx;
	i = -1;
	j = 0;
	printf("La le var c'est -%s-\n", var);
    printf("=====> Et dans add var on a :\n");
    // print_t_line(tmp);
	while (value[++i])
	{
		if (var[j] && tmp->c == var[j] && j == 0)
		{
            printf("Je rentre dans le replace\n");
			tmp = line_replace_node(tmp, value[i], idx);
			j++;
		}
		else
			tmp = line_add_node(tmp, value[i], idx);
		idx++;
	}
        printf("============\n");
        // print_t_line(line);
	rm_var_excess(line, index, var);
}