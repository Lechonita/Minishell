/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:21:34 by lechon            #+#    #+#             */
/*   Updated: 2023/06/27 10:22:33 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonction qui free tous les maillons de la liste chainee t_env. */

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs != NULL)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !(*env))
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->name)
		{
			free((*env)->name);
			(*env)->name = NULL;
		}
		if ((*env)->env_split)
			free_strs((*env)->env_split);
		free(*env);
		(*env) = tmp;
	}
	*env = NULL;
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
	if (data->history)
		free_strs(data->history);
	if (data->token)
		ft_free_token(data);
	if (data->env)
		ft_free_env(&data->env);
	free(data);
	data = NULL;
}
