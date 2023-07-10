/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:36:43 by Bea               #+#    #+#             */
/*   Updated: 2023/07/10 13:41:56 by jrouillo         ###   ########.fr       */
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
	INTEGER,
	DQUOTE,
	SQUOTE,
	NEW_LINE,
	BLANK,
	DOLLAR,
	PIPE,
	GREAT,
	LESS,
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
	WORD = 1,		[a-z A-Z +all]				1
	INTEGER,		[0-9]						2
	DQUOTE,			""							3
	SQUOTE,			''							4
	NEW_LINE,		\n							5
	BLANK,			space + \t					6
	DOLLAR,			$							7
	PIPE,			|							8
	GREAT,			>							9
	LESS,			<							10
	AMPERSAND,		&							13
	SEPARATOR,		; ( ) { }					14
	NOTOKEN,		invalid character in input	15

	REDIR = 20,		> < >> <<							20
	SIMPLE_CMD,		[a-z A-Z +all]						21
	BUILTIN,		echo cd pwd export unset env exit	22
	PIPEX,			|									23
*/

/* LINE INIT */
t_line	*line_last(t_line	*line);
void	line_addback(t_line *line, t_line *new);
t_line	*line_new(t_line *line, char c, int i);
void	init_line(t_bigshell *data, char *line);

/* FIND TYPE */
int		is_dollar(char c);
int		is_blank(char c);
int		is_single_quote(char c);
int		is_double_quote(char c);
int		is_integer(char c);
int		is_newline(char c);
int		is_ampersand(char c);
int		is_pipe(char c);
int		is_redir(char c);
int		is_separator(char c);
int		is_word(char c);
int		determine_type(char c);

/* FLAG QUOTES */
void	flag_double_quotes(t_line *line);
void	flag_single_quotes(t_line *line);

/* FIND TOKENS */
void	token_rm_next(t_token *tok);
void	create_token(t_bigshell *data, t_line *current, char *value, int pos);
void	find_tokens(t_bigshell *data);

/* GRAMMAR */
void	check_builtin(t_bigshell *data);
void	same_aim(t_bigshell *data);
void	add_arg_to_cmd(t_bigshell *data);
void	parser_job(t_bigshell *data);
void	apply_grammar(t_bigshell *data);

#endif