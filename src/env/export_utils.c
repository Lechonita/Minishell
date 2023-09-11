/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/11 12:06:57 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	end = equal + 1;
	while (input[end + 1])
	{
		if (ft_isalnum(input[end]) && !is_single_quote(input[end])
			&& !is_double_quote(input[end]) && input[end + 1] != ' ')
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

	start = equal - 1;
	while (start > 0)
	{
		if (ft_isalnum(input[start]) && input[start - 1] != ' ')
			start--;
		else
			break ;
	}
	return (start);
}
