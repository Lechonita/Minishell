/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:35:23 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/28 16:24:40 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "minishell.h"

void	redirection_here_doc(t_bigshell *data, t_redir *redir);
int		redirection_less(t_bigshell *data, t_redir *redir);
int		redirection_great(t_bigshell *data, t_redir *redir);
void	redirection_append(t_bigshell *data, t_redir *redir);

t_redir	*init_redir_in_cmd(t_token **token, int grp);


int		count_file(t_bigshell *data, int type);

t_redir	*init_redir(t_bigshell *data);
int		redir_job(t_bigshell *data);

void	handle_dup(t_bigshell *data, int pcss);

#endif