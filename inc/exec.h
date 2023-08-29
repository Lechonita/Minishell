/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:38:19 by Bea               #+#    #+#             */
/*   Updated: 2023/08/29 10:20:36 by Bea              ###   ########.fr       */
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
void	single_cmd(t_bigshell *data, t_simple_cmd *simple_cmd, char *env[]);
// pid_t	exec_cmd(t_bigshell *data, t_simple_cmd *cmd, char *env[], int end[2]);
int		exec_simple_cmd(t_bigshell *data, char *env[]);
int		executor(t_bigshell *data, char *env[]);

int		ft_waitpid(pid_t last_pid);

/* PIPE UTILS */
void	close_fd(t_bigshell *data, int idx, int type, int type2);
void	open_pipe(t_bigshell *data);
void	close_pipe(t_bigshell *data);

#endif