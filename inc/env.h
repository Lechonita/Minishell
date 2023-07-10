/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:31:27 by Bea               #+#    #+#             */
/*   Updated: 2023/07/10 13:36:05 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

/*  ENV INIT */
char	*get_env_name(char	*env);
void	init_env(t_bigshell *data, char **env);

/* SEARCH GOOD PATH */
void	get_path(t_bigshell *data);
// char	*find_path_to_cmd(t_bigshell *data, char *cmd);
char	*find_path_to_cmd(t_bigshell *data, char *cmd, char *path);

#endif