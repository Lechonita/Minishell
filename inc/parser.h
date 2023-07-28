/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:35 by Bea               #+#    #+#             */
/*   Updated: 2023/07/28 18:05:44 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int				open_fd(t_bigshell *data, t_redir *redir);


void			close_fd_in_cmd(t_redir *redir, int idx, int type, int type2);

int				count_file_in_cmd(t_redir *redir, int type);
t_redir			*last_redir_in_cmd(t_redir *redir, int type, int type2);

/* FIND AIM */
void			aim_redir(t_bigshell *data);
void			aim_pipe(t_bigshell *data);
void			aim_cmd(t_bigshell *data);
void			rm_blank(t_bigshell *data);
void			parser_job(t_bigshell *data);

/* AIM CMD */
void			token_group(t_token *tok);
void			same_aim(t_bigshell *data);
void			add_arg_to_cmd(t_bigshell *data);
void			check_builtin(t_bigshell *data);

/* SIMPLE CMD */
t_simple_cmd	*init_simple_cmd(void);
void			add_redir_to_cmd(t_bigshell *data);
void			add_in_out_to_cmd(t_bigshell *data);
void			add_cmd_to_cmd(t_bigshell *data);
void			merge_token_cmd(t_bigshell *data);

#endif