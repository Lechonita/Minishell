/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_find_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:11:05 by lechon            #+#    #+#             */
/*   Updated: 2023/06/09 14:41:55 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui determine le type du token pour le maillon en question.
	Ex: si la line = "echo hello" alors la valeur du premier maillon
	sera "echo" et son type sera TYPE_GENERIC */

/*int		get_argv_type(char *token)
{
	
}*/

// int	ft_determine_token(t_argv *new, char *line, int i)
// {
// 	if (line[0] == 39) // single quotes
// 		i = ft_quotes(new, line, 39, i);
// 	else if (line[0] == 34) // double quotes
// 		i = ft_quotes(new, line, 34, i);
// 	// else if (line[0] == '$') // env var (check si espace derriere ou pas)
// 	// 	ft_dollar_sign(new, line);
// 	// else if (line[0] == '>' || line[0] == '<') // redirections
// 	// 	ft_redirections(new, line);
// 	// else if (line[0] == '|') // pipe
// 	// 	ft_pipe(new, line);
// 	// else
// 	// 	ft_generic(new, line);
// 	return (i);
// }

/* Fonction qui determine la valeur du token pour le maillon en question.
	Ex: si la line = "echo hello" alors la valeur du premier maillon
	sera "echo". */

// char	*get_argv_value(char *line, int tkn_nb, int i, int j)
// {
// 	int		count;
// 	char	*value;

// 	count = 0;
// 	value = malloc(sizeof(char) * ft_strlen(line));
// 	if (value)
// 	{
// 		while (line[i])
// 		{
// 			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
// 				i++;
// 			if (line[i] && (line[i] != ' ' || line[i] == '\t'))
// 				count++;
// 			while (line[i] && (line[i] != ' ' || line[i] == '\t'))
// 			{
// 				if (count == tkn_nb + 1)
// 					value[j++] = line[i];
// 				i++;
// 			}
// 		}
// 	}
// 	value[j] = '\0';
// 	return (value);
// }

// void    get_argv_value_type(t_argv *new, char *line, int tkn_nb)
// {
// 	static int		i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
// 			i++;
// 		if (line[i] && (line[i] != ' ' || line[i] == '\t'))
// 			i = ft_determine_token(new, line + i, i);
// 	}
// }
