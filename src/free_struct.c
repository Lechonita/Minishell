/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/06/08 19:29:14 by lechon           ###   ########.fr       */
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

void    ft_free_history(t_bigshell *data)
{
	int		i;

	if (!data)
		return ;
	if (data->history)
	{
		i = -1;
		while(data->history[++i])
			free(data->history[i]);
		free(data->history);
	}
	else
		return ;
}

void	ft_free_all(t_bigshell *data)
{
	if (!data)
		return ;
	ft_free_history(data);
	ft_free_argv(data);
	ft_free_env(data);
	data = NULL;
}
