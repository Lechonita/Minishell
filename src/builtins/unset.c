/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:45:03 by Bea               #+#    #+#             */
/*   Updated: 2023/09/18 15:03:19 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_el(t_env *el)
{
	if (!el)
		return ;
	if (el->name)
		free(el->name);
	if (el->value)
		free(el->value);
	free(el);
}

void	update_idx(t_env *env)
{
	int		i;
	t_env	*el;

	i = 0;
	el = env;
	while (el)
	{
		el->index = i++;
		el = el->next;
	}
}

void	rm_env_el(t_env **env, char *to_remove)
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
	el = (*env)->next;
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
	update_idx(*env);
}

int	unset_var(char *cmd, char **args, t_bigshell *data)
{
	int		i;

	i = 1;
	dprintf(2, "je rentre dans unset var\n");
	if (cmd != NULL)
	{
		dprintf(2, "je rentre dans la boucle cmd != NULL\n");
		rm_env_el(&data->env, cmd);
		return (EXIT_SUCCESS);
	}
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
