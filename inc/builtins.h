/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:39:47 by Bea               #+#    #+#             */
/*   Updated: 2023/07/21 12:27:09 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		exec_builtin_cmd(t_bigshell *data, char *cmd, char **args);
int		exec_builtin_no_fork(t_bigshell *data, char *cmd, char **args);

int		change_directory(char **args, t_bigshell *data);
int		print_echo(char *cmd, char **args);
int		print_env(t_bigshell *data);
int		exit_shell(char **args, t_bigshell *data);
int		export_var(char *cmd, char **args, t_bigshell *data);
int		print_working_directory(t_bigshell *data);
int		unset_var(char *cmd, char **args, t_bigshell *data);

#endif