/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:35:23 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/13 17:36:05 by Bea              ###   ########.fr       */
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

t_redir	*init_redir(t_bigshell *data, int typ1, int typ2);
void	redir_job(t_bigshell *data);

char	*out_file_path(t_bigshell *data);
char	*in_file_path(t_bigshell *data);
void	handle_here_doc(t_bigshell *data, char *limiter);

void	handle_dup(t_bigshell *data, int pcss);

#endif