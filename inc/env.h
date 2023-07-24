/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:31:27 by Bea               #+#    #+#             */
/*   Updated: 2023/07/24 18:53:13 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

/*  ENV INIT */
t_env	*env_new(char *env, int idx, int to_export);
void	env_addback(t_env *env, t_env *new);
char	*get_env_name(char	*env);
void	init_env(t_bigshell *data, char **env);

/* SEARCH GOOD PATH */
void	get_path(t_bigshell *data);
char	*find_path_to_cmd(t_bigshell *data, char *cmd, char *path);

#endif