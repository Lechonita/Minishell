/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:38:19 by Bea               #+#    #+#             */
/*   Updated: 2023/09/11 16:00:29 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* EXEC */
void	single_cmd(t_bigshell *data, t_simple_cmd *simple_cmd, char *env[]);
int		exec_simple_cmd(t_bigshell *data, char *env[]);
int		executor(t_bigshell *data, char *env[]);

int		ft_waitpid(pid_t last_pid);

int	is_directory(char *msg, char *str);

#endif