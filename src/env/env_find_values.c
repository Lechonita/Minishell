/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:34:26 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 09:45:47 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_value(char *env)
{
	char	*value;
	int		i;

	i = find_equal(env);
	value = ft_strndup(env + i + 1, ft_strlen(env) - i);
	return (value);
}

int	find_equal(char *env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);
}

char	*get_env_name(char	*env)
{
	char	*name;
	int		i;

	i = find_equal(env);
	name = ft_strndup(env, i);
	return (name);
}
