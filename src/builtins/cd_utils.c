/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:49:49 by jrouillo          #+#    #+#             */
/*   Updated: 2023/07/27 16:39:55 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	find_next_index(t_bigshell *data)
// {
// 	t_env	*env;
// 	int		i;

// 	if (!data)
// 		return (-1);
// 	env = data->env;
// 	i = 0;
// 	while (env)
// 	{
// 		i++;
// 		env = env->next;
// 	}
// 	return (i);
// }

// t_env	*env_new_cd(t_bigshell *data, char *name, char *value)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return (NULL);
// 	new->name = name;
// 	new->value = value;
// 	new->index = find_next_index(data);
// 	new->to_export = FALSE;
// 	new->next = NULL;
// 	return (new);
// }

void	do_export_cd(t_bigshell *data, char *name, char *value)
{
	t_env	*env;

	if (!data)
		return ;
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			env->value = value;
			env->to_export = FALSE;
		}
		env = env->next;
	}
}
