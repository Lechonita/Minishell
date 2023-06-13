/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/06/13 17:07:54 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui free tous les maillons de la liste chainee t_env. */

void	ft_free_env(t_bigshell *data)
{
	t_env	*tmp;

	if (!data || !data->env)
		return ;
	while (data->env)
	{
		tmp = data->env->next;
		if (data->env->name)
			free(data->env->name);
		if (data->env->value)
			free(data->env->value);
		free(data->env);
		data->env = tmp;
	}
}

void	ft_free_argv(t_bigshell *data)
{
	t_argv	*tmp;

	if (!data || !data->argv)
		return ;
	while (data->argv)
	{
		tmp = data->argv->next;
		if (data->argv->value)
			free(data->argv->value);
		free(data->argv);
		data->argv = tmp;
	}
}

void	ft_free_history(t_bigshell *data)
{
	int		i;

	if (!data)
		return ;
	if (data->history)
	{
		i = 0;
		while (data->history[i])
		{
			free(data->history[i]);
			data->history[i] = NULL;
			i++;
		}
		free(data->history);
		data->history = NULL;
	}
}

void	ft_free_all(t_bigshell *data)
{
	if (!data)
		return ;
	if (data->history)
		ft_free_history(data);
	if (data->argv)
		ft_free_argv(data);
	if (data->env)
		ft_free_env(data);
	free(data);
	data = NULL;
}
