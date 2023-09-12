/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:47:10 by Bea               #+#    #+#             */
/*   Updated: 2023/09/12 18:31:24 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_back(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*last;

	last = (*lst);
	while (last -> next != NULL)
		last = last -> next;
	if (last == NULL)
	{
		*lst = new;
		return ;
	}
	if (lst && (*lst) && new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

static t_simple_cmd	*new_lst(int index)
{
	t_simple_cmd	*new;

	new = ft_calloc(1, sizeof(t_simple_cmd));
	new -> idx = index;
	new -> next = NULL;
	new -> prev = NULL;
	return (new);
}

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*simple_cmd;
	int				index;

	index = 0;
	simple_cmd = NULL;
	while (index < g_global.nb_cmd)
	{
		if (index == 0)
		{
			simple_cmd = new_lst(index);
			if (!simple_cmd)
				ft_error(EXIT_FAILURE, W_LST_CMD);
		}
		else
			add_back(&simple_cmd, new_lst(index));
		index++;
	}
	return (simple_cmd);
}
