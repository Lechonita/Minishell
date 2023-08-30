/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:35 by Bea               #+#    #+#             */
/*   Updated: 2023/08/30 12:05:06 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* FIND AIM */
void	aim_redir(t_bigshell *data);
void	aim_pipe(t_bigshell *data);
void	aim_cmd(t_bigshell *data);
void	rm_blank(t_bigshell *data);
void	parser_job(t_bigshell *data);

/* AIM CMD */
void	same_aim(t_bigshell *data);
char	*def_tok_value(char *value, char *next, char *nextnext);
void	add_arg_to_cmd(t_bigshell *data);
void	check_builtin(t_bigshell *data);

/* AIM UTILS */
char	*join_space(char *s1, char *s2, char *to_add);
int		last_is_dollar(char *str);

#endif