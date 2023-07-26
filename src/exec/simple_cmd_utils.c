/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:47:10 by Bea               #+#    #+#             */
/*   Updated: 2023/07/26 17:47:24 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_back(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*last;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	last = (*lst);
	while (last -> next != NULL)
		last = last -> next;
	last -> next = new;
}

static t_simple_cmd *new_lst(int index)
{
	t_simple_cmd	*new;

	new = ft_calloc(1, sizeof(t_simple_cmd));
	new -> idx = index;
	new -> next = NULL;
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
			simple_cmd = new_lst(index);
		else
			add_back(&simple_cmd, new_lst(index));
		index++;
	}
	return (simple_cmd);
}
