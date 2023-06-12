/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:34:26 by lechon            #+#    #+#             */
/*   Updated: 2023/06/08 17:37:26 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t		i;
	char		*copy;

	i = 0;
    copy = malloc(sizeof(char) * (n + 1));
    if (!copy)
		return (NULL);
	while (i < n && src[i])
	{
		copy[i] = src[i];
		i++;
	}
    copy[i] = '\0';
    return (copy);
}

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
