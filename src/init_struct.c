/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:01 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/02 15:59:15 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strncpy(char *dest, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_value(char *env)
{
	char	*value;
	int		i;

	i = find_equal(env);
	value = ft_strncpy(value, env + i + 1, ft_strlen(env) - i);
	return (value);
}

int	find_equal(char *env)
{
	int	i;

	i = -1;
	while (env[i] != '=')
		i++;
	return (i);
}

char	*get_name(char	*env)
{
	char	*name;
	int		i;

	i = find_equal(env);
	name = ft_strncpy(name, env, i);
	return (name);
}

/* Fonction qui rempli la structure t_env */

void	init_env(t_bigshell *data, char **env)
{
	t_env		*env;
	int			i;

	data->env = malloc(sizeof(t_env));
	if (!data->env)
		return (NULL);
	i = 0;
	data->env->name = get_name(env[i]);
	data->env->value = get_value(env[i]);
	printf("env name = %s\n", data->env->name);
	printf("env value = %s\n", data->env->value);
	// while (env[++i])
	// {
		
	// }
}

/* Fonction qui rempli la donnee bigshell->argv.
	Les cas de figures a prendre en compte :
	- s'il y a des guillemets au milieu des commandes (ex: l"s")
		= doit fonctionner normalement
	- s'il y a des guillements pour une string (ex: "hello world")
		= doit representer une seule commande
	Prochaines etapes : verifier ensuite si les commandes
		sont correctes (access) et puis les executer */

// void	init_argv(t_bigshell *data, int ac, char *av[])
// {

// }

/* Fonction qui regroupe toutes les fonctions d'initialisation pour les
	structures. Chacune des fonctions rempli une structure specifique. */

void	init_struct(t_bigshell *data, int ac, char *av[], char **env)
{
	// init_argv(ac, av);
	init_env(data, env);
}
