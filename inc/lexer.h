/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:36:43 by Bea               #+#    #+#             */
/*   Updated: 2023/07/14 17:59:46 by Bea              ###   ########.fr       */
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
	WORD = 1,
	DQUOTE,
	SQUOTE,
	NEW_LINE,
	BLANK,
	DOLLAR,
	PIPE,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	AMPERSAND,
	SEPARATOR,
	NOTOKEN,
};
# endif

/* Token aim */
enum e_aim
{
	REDIR = 20,
	SIMPLE_CMD,
	BUILTIN,
	PIPEX,
};

/*
	WORD = 1,		[a-z A-Z +all]	[0-9]		1
	DQUOTE,			""							2
	SQUOTE,			''							3
	NEW_LINE,		\n							4
	BLANK,			space + \t					5
	DOLLAR,			$							6
	PIPE,			|							7
	GREAT,			>							8
	DGREAT,			>>							9
	LESS,			<							10
	DLESS,			<<							11
	AMPERSAND,		&							12
	SEPARATOR,		; ( ) { }					13
	NOTOKEN,		invalid character in input	14

	REDIR = 20,		> < >> <<							20
	SIMPLE_CMD,		[a-z A-Z +all]						21
	BUILTIN,		echo cd pwd export unset env exit	22
	PIPEX,			|									23
*/

/* FIND TOKENS */
void	token_rm_next(t_token *tok);
void	create_token(t_bigshell *data, t_line *current, char *value, int pos);
void	find_tokens(t_bigshell *data);

/* GRAMMAR */
void	check_builtin(t_bigshell *data);
void	check_double_redir(t_bigshell *data);
void	same_aim(t_bigshell *data);
void	add_arg_to_cmd(t_bigshell *data);
void	parser_job(t_bigshell *data);
void	apply_grammar(t_bigshell *data);

#endif