/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:35:23 by bebigel           #+#    #+#             */
/*   Updated: 2023/08/30 16:15:47 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "minishell.h"

int	count_file(t_bigshell *data, int type);
int	open_fd(t_redir *redir);

int	redirection_here_doc(t_redir *redir);
int	redirection_less(t_redir *redir);
int	redirection_great(t_redir *redir);
int	redirection_append(t_redir *redir);

#endif