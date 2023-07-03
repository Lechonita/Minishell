/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:36:43 by Bea               #+#    #+#             */
/*   Updated: 2023/07/03 11:15:10 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# ifndef YYTOKENTYPE
#  define YYTOKENTYPE

/* Tokens.  */
enum e_tokentype
{
	WORD = 1,				// [a-z A-Z +all]			
	INTEGER,			// [0-9]						2
	DQUOTE,				// ""							3
	SQUOTE,				// ''							4
	NEWLINE,			// \n							5
	BLANK,				// space + \t					6
	DOLLAR,				// $							7
	PIPE,				// |							8	
	GREAT, 				// >							9
	LESS,				// <							10
	GREATGREAT,			// >>							11
	LESSLESS,			// <<							12
	AMPERSAND,			// &							13
	SEPARATOR,			// ; ( ) { }					14
	NOTOKEN,			// invalid character in input	15
};
# endif

// /* FIND TOKENS */
// void	ft_create_token(t_bigshell *data, t_line *current, char *value, int pos);
// void	find_tokens(t_bigshell *data);

#endif