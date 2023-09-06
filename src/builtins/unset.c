/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:45:03 by Bea               #+#    #+#             */
/*   Updated: 2023/09/06 21:30:18 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void free_el(t_env *el)
{
	if (!el)
		return ;
	if (el->name)
		free(el->name);
	if (el->value)
		free(el->value);
	free(el);
}

static void	rm_env_el(t_env **env, char *to_remove)
{
	t_env	*el;
	t_env	*prev;

	prev = *env;
	if (ft_strcmp((*env)->name, to_remove) == 0)
	{
		el = *env;
		*env = (*env)->next;
		free_el(el);
		return ;
	}
	el  = (*env)->next;
	while (el && ft_strcmp(el->name, to_remove))
	{
		prev = el;
		el = el->next;
	}
	if (el)
	{
		prev->next = el->next;
		free_el(el);
	}
}

int	unset_var(char **args, t_bigshell *data)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "PATH") == 0)
		{
			free_strs(data->env_paths);
			data->env_paths = NULL;
		}
		rm_env_el(&data->env, args[i++]);
	}
	return (EXIT_SUCCESS);
}
