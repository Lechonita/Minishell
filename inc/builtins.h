/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:39:47 by Bea               #+#    #+#             */
/*   Updated: 2023/09/15 15:20:17 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

char	*get_env_value(t_bigshell *data, char *name);
void	do_export_cd(t_bigshell *data, char *name, char *value);
void	rm_env_el(t_env **env, char *to_remove);

int		exec_builtin(t_bigshell *data, char *cmd, char **args, int fd_out);
int		print_echo(t_bigshell *data, char *cmd, char **args, int fd_out);
int		print_env(t_bigshell *data, char *cmd, char **args, int fd_out);
int		set_env_value(t_bigshell *data, char *name, char *value);
int		export_var(char **args, t_bigshell *data, int fd_out);
int		print_working_directory(t_bigshell *data, int fd_out);
int		unset_var(char *cmd, char **args, t_bigshell *data);
int		change_directory(char **args, t_bigshell *data);
int		get_export_value(t_bigshell *data, char *name);
int		exit_shell(char **args, t_bigshell *data);
int		update_pwd(t_bigshell *data);

#endif