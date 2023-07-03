/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:15:40 by Bea               #+#    #+#             */
/*   Updated: 2023/07/03 17:42:33 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*new_lst(int idx, char *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new -> cmd = ft_strdup(cmd);
	if (!new -> cmd)
		ft_exit(EXIT_FAILURE, W_LST_CMD_DUP);
	new -> cmd_arg = ft_split(cmd, ' ');
	if (!new -> cmd_arg)
		ft_exit(EXIT_FAILURE, W_SPLIT_CMD);
	new -> idx_cmd = idx;
	new -> next = NULL;
	return (new);
}

static t_cmd	*lst_last(t_cmd *lst)
{
	while (lst != NULL && lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

static void	lst_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	last = lst_last(*lst);
	last -> next = new;
}

t_cmd	*init_cmd(t_bigshell *data)
{
	t_cmd		*lst_cmd;
	t_token		*el;
	int			i;

	lst_cmd = NULL;
	el = data->token;
	i = 0;
	while (el != NULL)
	{
		if (i == 0 && el->aim == SIMPLE_CMD)
		{
			lst_cmd = new_lst(i, el->value);
			if (lst_cmd == NULL)
				return (NULL);
		}			
		else if (i > 0 && el->aim == SIMPLE_CMD)
			lst_add_back(&lst_cmd, new_lst(i, el->value));
		i++;
		el = el->next;
	}
	return (lst_cmd);
}
