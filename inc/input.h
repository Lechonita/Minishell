/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:33:54 by Bea               #+#    #+#             */
/*   Updated: 2023/07/20 16:43:04 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

void	catch_ctrl_d(t_bigshell *data, char *input);
void	ctrl_d_here_doc(char *input, char *limiter, int count);

void	free_readline(t_bigshell *data, char *input);
void	init_minishell(t_bigshell *data, char *env[]);

/* SIGNAL HANDLING */
void	set_signal_here_doc(void);
void	ft_sig_int(int sig);
void	set_signal(void);

#endif