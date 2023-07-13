/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:52:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/13 15:27:12 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

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
