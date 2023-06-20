/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:39:00 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 11:52:16 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_argv	*argv_last(t_argv	*argv)
// {
// 	while (argv && argv->next)
// 		argv = argv->next;
// 	return (argv);
// }

// void	argv_addback(t_argv *argv, t_argv *new)
// {
// 	t_argv	*last;

// 	if (!new)
// 		return ;
// 	if (!argv)
// 	{
// 		argv = new;
// 		return ;
// 	}
// 	last = argv_last(argv);
// 	last->next = new;
// }

/* Fonction qui cree un maillon t_argv pour ajouter a la
	liste chainee. */

// t_argv	*argv_new(char *line, int i)
// {
// 	t_argv	*new;

// 	new = malloc(sizeof(t_argv));
// 	if (!new)
// 		return (NULL);
// 	new->index = i;
// 	(void)line;
// 	get_argv_value_type(new, line, i);
// 	// new->value = get_argv_value(line, i, 0, 0);
// 	// printf("%d/ Ici mon new->value est => %s\n", i, new->value);
// 	// new->type = get_argv_type(new->value);
// 	new->next = NULL;
// 	return (new);
// }

int	is_separator(char c)
{
	if (c == '<' || c == '>' || c == 34 || c == 39 || c == '|')
		return (1);
	return (0);
}

int	ft_is_operator(char c)
{
	return (c == '&' || c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')');
}
