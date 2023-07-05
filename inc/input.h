/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:33:54 by Bea               #+#    #+#             */
/*   Updated: 2023/07/05 15:13:14 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

/* SIGNAL HANDLING */
void	catch_ctrl_d(t_bigshell *data, char *input);
void	ft_sig_int(int sig);
void	set_signal(void);

/* TERMINAL CAPABILITIES */
int		init_term(void);
int		ft_termcap(t_bigshell *data);

#endif