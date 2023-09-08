/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:36:43 by Bea               #+#    #+#             */
/*   Updated: 2023/09/08 15:00:55 by bebigel          ###   ########.fr       */
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

/* LINE INIT */
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
void	delete_squotes(t_line *line);
void	delete_dquotes(t_line *line);
void	rm_line_el(t_line **line);
int		flag_double_quotes(t_line *line);
int		flag_single_quotes(t_line *line);

/* FIND TOKENS */
void	token_rm_next(t_token *tok);
void	create_token(t_bigshell *data, t_line *current, char *value, int pos);
void	find_tokens(t_bigshell *data);

/* EXPORT PREP */
void	check_for_export(t_bigshell *data, t_line *line, char *input);

#endif

/*
	WORD = 1,		[a-z A-Z +all]	[0-9] =		1
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