/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/07 11:18:22 by lechon           ###   ########.fr       */
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
}

// void	display_env_struct(t_bigshell *data)
// {
// 	while (data->env)
// 	{
// 		printf("%s=%s\n", data->env->name, data->env->value);
// 		data->env = data->env->next;
// 	}
// }