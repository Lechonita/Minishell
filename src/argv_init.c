/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:39:00 by lechon            #+#    #+#             */
/*   Updated: 2023/06/19 17:13:01 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/********************************** INUTILE **********************************/

/* Fonction qui compte le nombre de tokens pour savoir combien
	de maillons creer dans la liste chainee t_argv. */

// int		ft_count_token(char *line)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (line[i])
// 	{
// 		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
// 			i++;
// 		if (line[i] && (line[i] != ' ' || line[i] == '\t'))
// 		{
// 			count++;
// 			printf("Je compte count ici. Mon line + %d = %s\n", i, line + i);
// 			i++;
// 		}
// 		while (line[i] && ((line[i] != ' ' || line[i] == '\t')
// 				&& !is_separator(line[i])))
// 			i++;
// 	}
// 	return (count);
// }

/* Fonction qui rempli la donnee data->argv.
	Les cas de figures a prendre en compte :
	- s'il y a des guillemets au milieu des commandes (ex: l"s")
		= doit fonctionner normalement
	- s'il y a des guillements pour une string (ex: "hello world")
		= doit representer une seule commande
	Prochaines etapes : verifier de quel type de token il s'agit (opérateur,
		redirection, commande, builtin, single quote, double quote)
		et le traiter en fonction. */

int	ft_is_operator(char c)
{
	return (c == '&' || c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')');
}

int	ft_find_first_quote(char *str)
{
	int		i;
	int		flag;
	char	quotetype;

	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			flag = 1;
			quotetype = str[i];
			break ;
		}
		i++;
	}
}

int	ft_find_quotes(char *str)
{
	int		i;
	int		flag;
	char	quotetype;

	i = 0;
	flag = 0;
	quotetype = NULL;
	while (str[i])
	{
		if (flag == 1 && str[i] == quotetype)
		{
			flag = 2;
			break ;
		}
		if (str[i] == 34 || str[i] == 39)
		{
			flag = 1;
			quotetype = str[i];
		}
		i++;
	}
	return (flag);
}

void	ft_lexer(t_bigshell *data, char *line, int i)
{
	// int		beg;
	// int		end;

	// beg = -1;
	// end = -1;
	// // fonction pour trouver position des quotes si y en a

	// if (ft_find_quotes(line) == 2)
	// {
	// 	beg = ft_find_first_quote(line);
	// 	end = ft_find_second_quote(line);
	// }
	if (i == 0 && line[i] == '\n')
	{
		// create token \n ;
		return ;
	}
	else if (line[i - 1] && is_operator(line[i - 1])
		&& is_operator(line[i]))
		ft__operator_token(data, line, i);
	else if ()
}

void	init_argv(t_bigshell *data, char *line)
{
	int		i;

	i = -1;

	while (line[++i])
	{
		// printf("Mon is_operator = %d\n", ft_is_operator(line[i]));
		ft_lexer(data, line, i);
		// if (i == 0)
		// 	data->argv = argv_new(line, i);
		// else
		// 	argv_addback(data->argv, argv_new(line, i));
	}
}
