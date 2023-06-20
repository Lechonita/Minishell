/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:39:00 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 09:45:44 by bebigel          ###   ########.fr       */
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

/* Fonction qui compte le nombre de tokens pour savoir combien
	de maillons creer dans la liste chainee t_argv. */

int	ft_count_token(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] && (line[i] != ' ' || line[i] == '\t'))
		{
			count++;
			printf("Je compte count ici. Mon line + %d = %s\n", i, line + i);
			i++;
		}
		while (line[i] && ((line[i] != ' ' || line[i] == '\t')
				&& !is_separator(line[i])))
			i++;
	}
	return (count);
}

/* Fonction qui rempli la donnee data->argv.
	Les cas de figures a prendre en compte :
	- s'il y a des guillemets au milieu des commandes (ex: l"s")
		= doit fonctionner normalement
	- s'il y a des guillements pour une string (ex: "hello world")
		= doit representer une seule commande
	Prochaines etapes : verifier de quel type de token il s'agit (opérateur,
		redirection, commande, builtin, single quote, double quote)
		et le traiter en fonction. */

void	init_argv(t_bigshell *data, char *line)
{
	// int		i;
	int		count_tkn;

	// i = -1;
	(void)data;
	count_tkn = ft_count_token(line);
	printf("Mon nombre de token est %d\n", count_tkn);
	// while (++i < count_tkn)
	// {
	// 	if (i == 0)
	// 		data->argv = argv_new(line, i);
	// 	else
	// 		argv_addback(data->argv, argv_new(line, i));
	// }
}
