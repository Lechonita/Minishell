/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:31:27 by Bea               #+#    #+#             */
/*   Updated: 2023/09/13 20:31:55 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

/*  ENV INIT */
t_env	*env_new(char *env, int idx, int to_export);
void	env_addback(t_env **env, t_env *new);
void	init_env(t_bigshell *data, char **env);

/* EXPORT */
int		start_pos(char *input, int equal);
int		end_pos(char *input, int equal);

/* SEARCH GOOD PATH */
void	get_path(t_bigshell *data);
char	*find_path_to_cmd(t_bigshell *data, char *cmd, char *path);

/* EXPORT UTILS */
void	unset_existing(t_bigshell *data, char *str);
int		is_export(t_line *line);

#endif