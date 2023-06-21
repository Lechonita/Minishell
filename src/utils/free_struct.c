/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 15:55:46 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	ft_free_token(t_bigshell *data)
{
	t_token	*tmp;

	if (!data || !data->token)
		return ;
	while (data->token)
	{
		tmp = data->token->next;
		if (data->token->value)
			free(data->token->value);
		free(data->token);
		data->token = tmp;
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
	if (data->token)
		ft_free_token(data);
	if (data->env)
		ft_free_env(data);
	free(data);
	data = NULL;
}
