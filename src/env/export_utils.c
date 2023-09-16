/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/16 18:38:09 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_for_expansion(t_bigshell *data, char *str)
{
	char	*name;
	char	*value;
	char	*var;

	value = find_value(str);
	if (ft_strchr(value, '$') != NULL)
	{
		name = find_name(str);
		var = take_after_dollar(value);
		compare_env_var(data, var, name);
		free(name);
		free(var);
	}
	free(value);
}

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
