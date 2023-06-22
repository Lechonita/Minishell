/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:41:41 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/22 12:14:04 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H 

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

#endif