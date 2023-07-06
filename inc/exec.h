/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:38:19 by Bea               #+#    #+#             */
/*   Updated: 2023/07/05 15:13:35 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* EXEC INIT */
t_cmd	*init_cmd(t_bigshell *data);
void	init_exec(t_bigshell *data);

/* REDIRECTION */
void	handle_here_doc(t_bigshell *data, char *limiter);
void	redir_in_file(t_bigshell *data);
void	redir_out_file(t_bigshell *data);

/* EXEC */
pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss);
int		ft_waitpid(pid_t last_pid);
int		executor(t_bigshell *data, char *env[]);

/* PIPE UTILS */
void	open_pipe(t_bigshell *data);
void	close_pipe(t_bigshell *data);
void	handle_dup(t_bigshell *data, int pcss);

#endif