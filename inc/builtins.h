/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:39:47 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 16:41:16 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		exec_builtin_cmd(t_bigshell *data, char *cmd, char **args);
int		exec_builtin_no_fork(t_bigshell *data, char *cmd, char **args);

void	do_export_cd(t_bigshell *data, char *name, char *value);
int		change_directory(char **args, t_bigshell *data);
int		print_echo(char *cmd, char **args);
int		print_env(t_bigshell *data);
int		exit_shell(char **args, t_bigshell *data);
int		export_var(char **args, t_bigshell *data);
int		print_working_directory(t_bigshell *data);
int		unset_var(char **args, t_bigshell *data);

#endif