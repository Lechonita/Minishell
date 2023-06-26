/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/26 10:56:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonction qui cherche la dernier maillon de la liste chainee t_env. */

static t_env	*env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

/* Fonction qui ajoute un nouveau maillon a la liste
	chainee deja existante t_env. */

static void	env_addback(t_env *env, t_env *new)
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

/* Fonction qui delimite le nom de la ligne de l'env */

char	*get_env_name(char	*env)
{
	char	*name;
	int		pos_equal;

	pos_equal = 0;
	while (env[pos_equal] != '=')
		pos_equal++;
	name = ft_strndup(env, pos_equal);
	return (name);
}

/* Fonction qui cree un maillon t_env pour ajouter a la liste chainee. */

static t_env	*env_new(char *env, int idx)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = get_env_name(env);
	new->value = getenv(new->name);
	new->env_paths = NULL;
	new->index = idx;
	new->next = NULL;
	return (new);
}

/* Fonction qui rempli la structure t_env. C'est la creation
	de la liste chainee t_env. */

void	init_env(t_bigshell *data, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (i == 0)
		{
			data->env = env_new(env[i], i);
			if (!data->env)
				ft_exit(EXIT_FAILURE, W_NO_ENV);
		}
		else
			env_addback(data->env, env_new(env[i], i));
	}
	get_path(data);
}
