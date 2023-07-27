/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:35 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 12:46:46 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void			add_redir_to_cmd(t_bigshell *data);
int				open_fd(t_bigshell *data, t_redir *redir);

void			add_in_out_to_cmd(t_bigshell *data);
void			close_fd_in_cmd(t_redir *redir, int idx, int type, int type2);

int				count_file_in_cmd(t_redir *redir, int type);
char			*out_file_path_in_cmd(t_simple_cmd *cmd);
char			*in_file_path_in_cmd(t_simple_cmd *cmd);
t_redir			*last_redir_in_cmd(t_redir *redir, int type, int type2);

/* FIND AIM */
void			aim_redir(t_bigshell *data);
void			aim_pipe(t_bigshell *data);
void			aim_cmd(t_bigshell *data);
void			rm_blank(t_bigshell *data);
void			parser_job(t_bigshell *data);

/* AIM CMD */
t_simple_cmd	*init_simple_cmd(void);
void			token_group(t_token *tok);
void			same_aim(t_bigshell *data);
void			add_arg_to_cmd(t_bigshell *data);
void			check_builtin(t_bigshell *data);

#endif