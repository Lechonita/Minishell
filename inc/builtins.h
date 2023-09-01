/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:39:47 by Bea               #+#    #+#             */
/*   Updated: 2023/09/01 12:45:41 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

t_env	*env_new_cd(t_bigshell *data, char *name, char *value);
int		get_export_value(t_bigshell *data, char *name);

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