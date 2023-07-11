/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:52:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/10 13:42:00 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

int	is_dollar(char c)
{
	if (c == '$')
		return (DOLLAR);
	return (0);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (BLANK);
	return (0);
}

int	is_single_quote(char c)
{
	if (c == '\'')
		return (SQUOTE);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == '\"')
		return (DQUOTE);
	return (0);
}

int	is_integer(char c)
{
	if (c >= '0' && c <= '9')
		return (INTEGER);
	return (0);
}