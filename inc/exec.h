/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:38:19 by Bea               #+#    #+#             */
/*   Updated: 2023/07/17 17:04:49 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* EXEC INIT */
char	*out_file_path(t_bigshell *data);
char	*in_file_path(t_bigshell *data);
t_redir	*last_redir(t_bigshell *data, int type, int type2);
t_cmd	*init_cmd(t_bigshell *data);
void	init_exec(t_bigshell *data);

/* EXEC */
pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss);
pid_t	exec_simple_cmd(t_bigshell *data, char *env[]);
int		executor(t_bigshell *data, char *env[]);

int		ft_waitpid(pid_t last_pid);

/* PIPE UTILS */
void	close_fd(t_bigshell *data, int idx, int type, int type2);
// void	close_fd(t_bigshell *data);
void	open_pipe(t_bigshell *data);
void	close_pipe(t_bigshell *data);

#endif