/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/15 17:28:37 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Comparer les noms des maillons t_env avec les valeurs des maillons t_env.
	Si on trouve une valeur "$USER", alors il prendra la valeur du maillon
	t_env qui possède le nom USER. */

// void	check_for_expansion(t_bigshell *data)
// {
// 	t_env	*value;
// 	t_env	*name;

// 	value = data->env;
// 	name = data->env;
// 	while (value)
// 	{
// 		while (name)
// 		{
// 			if (!ft_strncmp(name->name, value->value, ft_strlen(value->value) - '$'))
				
// 			name = name->next;
// 		}
// 		value = value->next;
// 	}
// }

static int	add_len_in_quotes(char *input, int open_quote)
{
	int	size;
	int	i;

	size = 0;
	i = open_quote;
	while (input[i] && input[i] != '\n')
	{
		if (is_single_quote(input[i]) || is_double_quote(input[i]))
			break ;
		size++;
		i++;
	}
	return (size);
}

int	end_pos(char *input, int equal)
{
	int		end;

	if (equal == 0)
		return (ft_strlen(input) - 1);
	end = equal + 1;
	while (input[end] && input[end + 1])
	{
		if ((ft_isalnum(input[end]) || input[end] == '$')
			&& !is_single_quote(input[end]) && !is_double_quote(input[end])
			&& input[end + 1] != ' ')
			end++;
		else if (is_single_quote(input[end]) || is_double_quote(input[end]))
		{
			end += add_len_in_quotes(input, end + 1);
			break ;
		}
		else
			break ;
	}
	return (end);
}

int	start_pos(char *input, int equal)
{
	int		start;

	if (equal == 0)
	{
		start = ft_strlen(input);
		while (start || input[start])
		{
			if (input[start] == ' ')
				break ;
			start--;
		}
		start += 1;
	}
	else
	{
		start = equal - 1;
		while (start > 0)
		{
			if (ft_isalnum(input[start]) && input[start - 1] != ' ')
				start--;
			else
				break ;
		}
	}
	return (start);
}

int	is_export(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && i < 6)
		if (line[i] != "export"[i])
			return (FALSE);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_isalnum(line[i]) == 0)
		return (FALSE);
	return (TRUE);
}
