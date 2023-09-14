/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:34:37 by Bea               #+#    #+#             */
/*   Updated: 2023/09/14 16:04:16 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/lexer.h"

int	is_newline(char c)
{
	if (c == '\n')
		return (NEWLINE);
	return (0);
}

int	is_ampersand(char c)
{
	if (c == '&')
		return (AMPERSAND);
	return (0);
}

int	is_redir(char c)
{
	if (c == '>')
		return (GREAT);
	if (c == '<')
		return (LESS);
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (PIPE);
	return (0);
}
