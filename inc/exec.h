/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:38:19 by Bea               #+#    #+#             */
/*   Updated: 2023/07/13 17:39:10 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/* EXEC INIT */
t_cmd	*init_cmd(t_bigshell *data);
void	init_exec(t_bigshell *data);
int		count_file(t_bigshell *data, int type);

/* EXEC */
pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss);
pid_t	exec_simple_cmd(t_bigshell *data, char *env[]);
int		executor(t_bigshell *data, char *env[]);

int		ft_waitpid(pid_t last_pid);

/* PIPE UTILS */
void	open_pipe(t_bigshell *data);
void	close_pipe(t_bigshell *data);

#endif