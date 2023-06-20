/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:13:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/20 13:53:53 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_integer(char c)
{
	if (c >= '0' && c <= '9')
		return (4);
	return (0);
}

int	ft_is_word(char c)
{
	if (!ft_is_separator(c) && !ft_is_operator(c) && !ft_is_blank(c)
		&& !ft_is_single_quote(c) && !ft_is_double_quote(c)
		&& !ft_is_integer(c))
		return (3);
	return (0);
}

int	ft_is_operator(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')')
		return (2);
	return (0);
}

int	ft_is_separator(char c)
{
	if (c == '(' || c == ')' || c == '{' || c == '}')
		return (1);
	return (0);
}

int	ft_determine_type(char c)
{
	int		res;

	res = 0;
	if (ft_is_separator(c))
		res = 1;
	else if (ft_is_operator(c))
		res = 2;
	else if (ft_is_word(c))
		res = 3;
	else if (ft_is_integer(c))
		res = 4;
	else if (ft_is_double_quote(c))
		res = 5;
	else if (ft_is_single_quote(c))
		res = 6;
	else if (ft_is_blank(c))
		res = 7;
	return (res);
}
