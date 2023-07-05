/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:35 by Bea               #+#    #+#             */
/*   Updated: 2023/07/05 15:14:03 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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

/* FIND QUOTES */
int		find_closing_quote(t_line *line, int type);
void	convert_quotes(t_line *line, int type);
void	find_quotes(t_line *line);
void	flag_double_quotes(t_line *line);
void	flag_single_quotes(t_line *line);

#endif