/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:31:27 by Bea               #+#    #+#             */
/*   Updated: 2023/09/18 16:41:43 by jrouillo         ###   ########.fr       */
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

/* EXPORT UTILS */

void	unset_existing(t_bigshell *data, char *str);

#endif