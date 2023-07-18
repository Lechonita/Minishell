/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:39:47 by Bea               #+#    #+#             */
/*   Updated: 2023/07/18 12:11:21 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	change_directory(char **args, t_bigshell *data);
void	print_echo(char *cmd, char **args, t_bigshell *data);
void	print_env(t_bigshell *data);
void	exit_shell(char *cmd, char **args, t_bigshell *data);
void	export_var(char *cmd, char **args, t_bigshell *data);
void	print_working_directory(void);
void	unset_var(char *cmd, char **args, t_bigshell *data);

#endif