/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/06/22 17:18:00 by bebigel          ###   ########.fr       */
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

void	ft_free_all(t_bigshell *data)
{
	if (!data)
		return ;
	rl_clear_history();
	if (data->token)
		ft_free_token(data);
	if (data->env)
		ft_free_env(data);
	free(data);
	data = NULL;
}
