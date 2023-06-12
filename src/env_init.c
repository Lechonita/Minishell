/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/08 17:37:26 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui cherche la dernier maillon de la liste chainee t_env. */

t_env	*env_last(t_env *env)
{
	while(env && env->next)
		env = env->next;
	return (env);
}

/* Fonction qui ajoute un nouveau maillon a la liste
	chainee deja existante t_env. */

void	env_addback(t_env *env, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!env)
	{
		env = new;
		return ;
	}
	last = env_last(env);
	last->next = new;
}

/* Fonction qui cree un maillon t_env pour ajouter a la
	liste chainee. */

t_env	*env_new(char *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = get_env_name(env);
	new->value = get_env_value(env);
	new->next = NULL;
	return (new);
}

/* Fonction qui rempli la structure t_env. C'est la creation
	de la liste chainee t_env. */

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

/* fonction qui permet d'afficher t_env
	(equivalent de la commande "env" dans le terminal) */

// void	display_env_struct(t_bigshell *data)
// {
// 	while (data->env)
// 	{
// 		printf("%s=%s\n", data->env->name, data->env->value);
// 		data->env = data->env->next;
// 	}
// }