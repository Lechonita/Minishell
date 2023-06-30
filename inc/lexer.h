/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:36:43 by Bea               #+#    #+#             */
/*   Updated: 2023/06/30 16:11:50 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# ifndef YYTOKENTYPE
#  define YYTOKENTYPE

enum e_tokentype
{
	WORD = 258,
	NOTOKEN = 259,
	GREAT = 260,
	NEWLINE = 261,
	LESS = 262,
	GREATGREAT = 263,
	LESSLESS = 264,
	AMPERSAND = 265,
	GREATAMPERSAND = 266,
	GREATGREATAMPERSAND = 267,
	PIPE = 268,
	INTEGERGREAT = 269
};
# endif

/* Tokens.  */
# define WORD 258					// word
# define NOTOKEN 259				// invalid character in input
# define GREAT 260					// >
# define NEWLINE 261				// \n
# define LESS 262					// <
# define GREATGREAT 263				// >>
# define LESSLESS 264				// <<
# define AMPERSAND 265				// &
# define GREATAMPERSAND 266			// >&
# define GREATGREATAMPERSAND 267	// >>&
# define PIPE 268					// |
# define INTEGERGREAT 269			// >[0-9]+

// /* FIND TOKENS */
// void	ft_create_token(t_bigshell *data, t_line *current, char *value, int pos);
// void	find_tokens(t_bigshell *data);

#endif