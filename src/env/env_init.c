/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/14 15:56:06 by jrouillo         ###   ########.fr       */
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
	while (env[pos_equal] && env[pos_equal] != '=')
		pos_equal++;
	if (pos_equal == ft_strlen(env))
		name = ft_strdup(env);
	else
		name = ft_strndup(env, pos_equal);
	return (name);
}

static char	*get_env_for_export(char *env)
{
	char	*value;
	int		pos_equal;

	pos_equal = 0;
	while (env[pos_equal] && env[pos_equal] != '=')
		pos_equal++;
	if (ft_strlen(env) == pos_equal)
		return (NULL);
	value = ft_strdup(env + pos_equal + 1);
	return (value);
}

t_env	*env_new(char *env, int idx, int to_export)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->name = get_env_name(env);
	new->to_export = to_export;
	if (to_export == TRUE)
	{
		new->value = get_env_for_export(env);
		if (new->value == NULL)
			new->to_export = 2;
		else
			new->to_export = FALSE;
	}
	else
		new->value = ft_strdup(getenv(new->name));
	new->index = idx;
	new->next = NULL;
	return (new);
}

void	init_env(t_bigshell *data, char **env)
{
	int		i;
	t_env	*new;

	i = -1;
	while (env[++i])
	{
		new = env_new(env[i], i, FALSE);
		if (!new)
			ft_error(EXIT_FAILURE, W_NO_ENV);
		env_addback(&data->env, new);
	}
	get_path(data);
	set_env_value(data, "OLDPWD", get_env_value(data, "PWD"));
}
