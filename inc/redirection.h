/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:35:23 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/11 15:55:08 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "minishell.h"

// /* redir  */
// enum e_access
// {
// 	NO_ACCESS = 1,
// 	RD_ACCESS,
// 	WR_ACCESS,
// 	RDWR_ACCESS,
// };

void	redirection_here_doc(t_bigshell *data, t_redir *redir);

t_redir	*init_redir(t_bigshell *data, int type);
void	redir_job(t_bigshell *data);

void	redir_in_file(t_bigshell *data);
void	redir_out_file(t_bigshell *data);
void	handle_here_doc(t_bigshell *data, char *limiter);

void	handle_dup(t_bigshell *data, int pcss);

#endif