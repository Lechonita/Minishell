/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:45:03 by Bea               #+#    #+#             */
/*   Updated: 2023/09/06 18:11:43 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	emv_rm_next(t_env *env_to_rm)
{
	t_env	*tmp;

	if (!env_to_rm || !env_to_rm->next)
		return ;
	tmp = env_to_rm->next;
	env_to_rm->next = env_to_rm->next->next;
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

static void	rm_env_el(t_bigshell *data, int idx)
{
	t_env	*el;

	el = data->env;
	dprintf(2, "rm_env_el: idx = %d\n", idx);
	if (el->index == idx)
	{
		data->env = el->next;
		free(el->name);
		free(el->value);
		free(el);
		return ;
	}
	while (el && el->next && el->next->next)
	{
		dprintf(2, "rm_env_el: el->index = %d\n", el->index);
		if (el->next && el->next->index == idx)
			emv_rm_next(el);
		el = el->next;
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
		while (el && el->next && el->next->next)
		{
			if (ft_strcmp(el->name, args[i]) == 0)
				rm_env_el(data, el->index);
			dprintf(2, "unset_var: [%d] %s\n", el->index, el->name);
			if (el)
				el = el->next;
			else
				break ;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
