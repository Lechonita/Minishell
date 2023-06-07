/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/06/07 11:34:48 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui free les malloc de la fonction ft_strndup.
	La fonction ft_strndup nous a permis de recuperer les noms des
	variables d'environnement. */

void	ft_free_env_names(t_bigshell *data)
{
	while (data->env->name)
	{
		free(data->env->name);
		data->env = data->env->next;
	}
}
/* Fonction qui free les malloc de la fonction ft_strndup.
	La fonction ft_strndup nous a permis de recuperer les valeurs des
	variables d'environnement. */

void	ft_free_env_values(t_bigshell *data)
{
	while (data->env->value)
	{
		free(data->env->value);
		data->env = data->env->next;
	}
}

/* Fonction qui free tous les maillons de la liste chainee t_env. */

void	ft_free_env(t_bigshell *data)
{
	t_bigshell	*tmp;

	if (!data)
		return ;
	ft_free_env_names(data);
	ft_free_env_values(data);
	while (data->env)
	{
		tmp = data->env->next;
		free(data->env);
		data->env = tmp;
	}
}