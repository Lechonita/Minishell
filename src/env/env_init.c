/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/04 18:04:59 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

void	env_addback(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!(*env))
	{
		(*env) = new;
		return ;
	}
	last = (*env);
	while (last->next)
		last = last->next;
	last->next = new;
}

static char	*get_env_name(char	*env)
{
	char	*name;
	int		pos_equal;

	pos_equal = 0;
	while (env[pos_equal] != '=')
		pos_equal++;
	name = ft_strndup(env, pos_equal);
	return (name);
}

static char	*get_env_for_export(char *env)
{
	char	*value;
	int		pos_equal;

	pos_equal = 0;
	while (env[pos_equal] != '=')
		pos_equal++;
	if (ft_strlen(env) == pos_equal)
		return (env);
	value = ft_strdup(env + pos_equal + 1);
	return (value);
}

t_env	*env_new(char *env, int idx, int to_export)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = get_env_name(env);
	dprintf(2, "name => %8s", new->name);
	if (to_export == TRUE)
		new->value = get_env_for_export(env);
	else
		new->value = ft_strdup(getenv(new->name));
	dprintf(2, " %s\n", new->value);
	new->index = idx;
	dprintf(2, "index = %2d ", new->index);
	new->to_export = to_export;
	dprintf(2, "to_export = %d\n", new->to_export);
	new->next = NULL;
	return (new);
}

void	init_env(t_bigshell *data, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (i == 0)
		{
			data->env = env_new(env[i], i, FALSE);
			if (!data->env)
				ft_exit(EXIT_FAILURE, W_NO_ENV);
		}
		else
			env_addback(&data->env, env_new(env[i], i, FALSE));
	}
	get_path(data);
}
