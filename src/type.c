/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:13:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/20 14:42:33 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_integer(char c)
{
	if (c >= '0' && c <= '9')
		return (TYPE_INTEGER);
	return (0);
}

int	ft_is_word(char c)
{
	if (!ft_is_separator(c) && !ft_is_operator(c) && !ft_is_blank(c)
		&& !ft_is_single_quote(c) && !ft_is_double_quote(c)
		&& !ft_is_integer(c))
		return (TYPE_WORD);
	return (0);
}

int	ft_is_operator(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')')
		return (TYPE_OPERATOR);
	return (0);
}

int	ft_is_separator(char c)
{
	if (c == '(' || c == ')' || c == '{' || c == '}')
		return (TYPE_SEPARATOR);
	return (0);
}

int	ft_determine_type(char c)
{
	int		res;

	res = 0;
	if (ft_is_separator(c))
		res = TYPE_SEPARATOR;
	else if (ft_is_operator(c))
		res = TYPE_OPERATOR;
	else if (ft_is_word(c))
		res = TYPE_WORD;
	else if (ft_is_integer(c))
		res = TYPE_INTEGER;
	else if (ft_is_double_quote(c))
		res = TYPE_DOUBLE_QUOTES;
	else if (ft_is_single_quote(c))
		res = TYPE_SINGLE_QUOTES;
	else if (ft_is_blank(c))
		res = TYPE_BLANK;
	return (res);
}
