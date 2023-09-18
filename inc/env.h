/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:31:27 by Bea               #+#    #+#             */
/*   Updated: 2023/09/18 15:18:53 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

/*  ENV INIT */
t_env	*env_new(char *env, int idx, int to_export);
char	*find_path_to_cmd(t_bigshell *data, char *cmd, char *path);
void	init_env(t_bigshell *data, char **env);
void	env_addback(t_env **env, t_env *new);
int		get_path(t_bigshell *data);

/* EXPORT */
int		end_pos(char *input, int equal);
int		start_pos(char *input, int equal);

/* EXPORT UTILS */
t_env	*init_var(t_bigshell *data, char *name, char *value);
void	check_for_expansion(t_bigshell *data, char *str);
void	unset_existing(t_bigshell *data, char *str);
int		is_export(t_line *line);

/* EXPORT EXPANSION */
void	compare_env_var(t_bigshell *data, char *var, char *name);
char	*take_after_dollar(char *str);
char	*find_value(char *str);
char	*find_name(char *str);

#endif