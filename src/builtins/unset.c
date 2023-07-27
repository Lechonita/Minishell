/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:45:03 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 17:11:48 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unset_var(char **args, t_bigshell *data)
{
	int		i;
	t_env	*el;

	i = 1;
	while (args[i])
	{
		el = data->env;
		while (el)
		{
			if (ft_strcmp(el->name, args[i]) == 0)
				el->to_export = TRUE;
			el = el->next;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
