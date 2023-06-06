/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/06 17:29:59 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_last(t_env *new)
{
	while(new && new->next)
		new = new->next;
	return (new);
}

void	env_addback(t_env *new, t_env *env)
{
	t_env	*last;

	if (!env)
		return ;
	if (!new)
	{
		new = env;
		return ;
	}
	last = env_last(new);
	last->next = env;
}

t_env	*env_new(char *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = get_name(env);
	new->value = get_value(env);
	new->next = NULL;
	return (new);
}

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

char	*get_value(char *env)
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

char	*get_name(char	*env)
{
	char	*name;
	int		i;

	i = find_equal(env);
	name = ft_strndup(env, i);
	return (name);
}

/* Fonction qui rempli la structure t_env */

void	init_env(t_bigshell *data, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if ( i == 0)
			data->env = env_new(env[i]);
		else
			env_addback(data->env, env_new(env[i]));
	}
	// display_env_struct(data);
}

// void	display_env_struct(t_bigshell *data)
// {
// 	while (data->env)
// 	{
// 		printf("%s=%s\n", data->env->name, data->env->value);
// 		data->env = data->env->next;
// 	}
// }void	display_env_struct(t_bigshell *data)
// {
// 	while (data->env)
// 	{
// 		printf("%s=%s\n", data->env->name, data->env->value);
// 		data->env = data->env->next;
// 	}
// }