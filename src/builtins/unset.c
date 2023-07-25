/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:45:03 by Bea               #+#    #+#             */
/*   Updated: 2023/07/25 12:08:50 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	rm_one_for_unset(t_env **env)
{
	t_env	*el;
	t_env	*head;

	head = *env;
	while (head->next)
	{
		if (head->next->to_export == TRUE)
		{
			el = head->next;
			free(head->next->name);
			free(head->next->value);
			head->next = head->next->next;
			free(el);
		}
		else
			env = &head->next;
	}
}

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
	rm_one_for_unset(&data->env);
	return (EXIT_SUCCESS);
}
