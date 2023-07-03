/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:13:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/03 11:17:05 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

int	is_word(char c)
{
	if (!is_separator(c) && !is_blank(c) && !is_integer(c) && !is_dollar(c)
		&& !is_single_quote(c) && !is_double_quote(c) && !is_newline(c)
		&& !is_ampersand(c) && !is_redir(c) && !is_pipe(c))
		return (WORD);
	return (0);
}

int	determine_type(char c)
{
	if (is_separator(c))
		return (SEPARATOR);
	else if (is_newline(c))
		return (NEWLINE);
	else if (is_word(c))
		return (WORD);
	else if (is_integer(c))
		return (INTEGER);
	else if (is_double_quote(c))
		return (DQUOTE);
	else if (is_single_quote(c))
		return (SQUOTE);
	else if (is_blank(c))
		return (BLANK);
	else if (is_dollar(c))
		return (DOLLAR);
	else if (is_ampersand(c))
		return (AMPERSAND);
	else if (is_redir(c) == GREAT)
		return (GREAT);
	else if (is_redir(c) == LESS)
		return (LESS);
	else if (is_pipe(c))
		return PIPE;
	return (NOTOKEN);
}
