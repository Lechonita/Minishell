/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/12 15:23:43 by bebigel          ###   ########.fr       */
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
	dprintf(2, "\033[1;39menv name %s\033[0m\n", env);
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

	new = ft_calloc(1, sizeof(t_env));
	dprintf(2, "\033[1;39menv_new \033[0m");
	new->name = get_env_name(env);
	dprintf(2, "\033[1;39mname %s\033[0m\n", new->name);
	if (to_export == TRUE)
		new->value = get_env_for_export(env);
	else
		new->value = ft_strdup(getenv(new->name));
	new->index = idx;
	new->to_export = to_export;
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
	set_env_value(data, "OLDPWD", get_env_value(data, "PWD"));
}
