/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:35 by Bea               #+#    #+#             */
/*   Updated: 2023/08/30 16:50:58 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* FIND AIM */
void			parser_job(t_bigshell *data);

/* AIM CMD */
void	same_aim(t_bigshell *data);
char	*def_tok_value(char *value, char *next, char *nextnext);
void	add_arg_to_cmd(t_bigshell *data);
void	check_builtin(t_bigshell *data);

/* AIM UTILS */
char	*join_spac(char *s1, char *s2, char *to_add);
int		last_is_dollar(char *str);
void			token_group(t_token *tok);
void			same_aim(t_bigshell *data);
void			add_arg_to_cmd(t_bigshell *data);
void			check_builtin(t_bigshell *data);

/* SIMPLE CMD */
t_simple_cmd	*init_simple_cmd(void);
void			add_redir(t_bigshell *data);
void			add_io(t_bigshell *data);
void			add_cmd_to_lst(t_bigshell *data);
void			merge_token_cmd(t_bigshell *data);
int				nb_red_in_cmd(t_redir *redir, int type);

#endif