/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:33:54 by Bea               #+#    #+#             */
/*   Updated: 2023/09/12 15:16:22 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

void		free_readline(t_bigshell *data, char *input);
t_bigshell	*locate_shell(t_bigshell *data, int status);

/* SIGNAL HANDLING */
void		ctrl_d_here_doc(char *input, char *limiter);
void		set_signal_here_doc(void);
void		set_signal_child(void);
void		ft_sig_int(int sig);
void		set_signal(void);

#endif