/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:35 by Bea               #+#    #+#             */
/*   Updated: 2023/07/26 18:07:42 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

void			add_redir_to_cmd(t_bigshell *data);

/* FIND AIM */
void 			aim_redir(t_bigshell *data);
void 			aim_pipe(t_bigshell *data);
void 			aim_cmd(t_bigshell *data);
void 			rm_blank(t_bigshell *data);
void 			parser_job(t_bigshell *data);

/* AIM CMD */
t_simple_cmd	*init_simple_cmd(void);
void 			token_group(t_token *tok);
void 			same_aim(t_bigshell *data);
void 			add_arg_to_cmd(t_bigshell *data);
void 			check_builtin(t_bigshell *data);

#endif