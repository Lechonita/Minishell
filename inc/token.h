/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:41:41 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/13 11:47:18 by bebigel          ###   ########.fr       */
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
	AMPERSAND = 264,
	GREATAMPERSAND = 265,
	GREATGREATAMPERSAND = 266,
	PIPE = 267,
	INTEGERGREAT = 268
};
# endif

/* Tokens.  */
# define WORD 258					// word
# define NOTOKEN 259				// invaid character in input
# define GREAT 260					// >
# define NEWLINE 261				// \n
# define LESS 262					// <
# define GREATGREAT 263				// >>
# define AMPERSAND 264				// &
# define GREATAMPERSAND 265			// >&
# define GREATGREATAMPERSAND 266	// >>&
# define PIPE 267					// |
# define INTEGERGREAT 268			// >[0-9]+

#endif