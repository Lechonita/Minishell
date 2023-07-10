/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/10 10:47:03 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






#include "../inc/minishell.h"

static t_cmd	*new_lst(t_bigshell *data, int idx, char *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new -> cmd = ft_strdup(cmd);
	if (!new -> cmd)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_CMD_DUP), NULL);
	new -> cmd_arg = ft_split(cmd, ' ');
	if (!new -> cmd_arg)
		return (free_all(data), ft_exit(EXIT_FAILURE, W_SPLIT_CMD), NULL);
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
		if (i == 0 && (el->aim == SIMPLE_CMD || el->aim == BUILTIN))
		{
			lst_cmd = new_lst(data, i++, el->value);
			if (lst_cmd == NULL)
				return (free_all(data), ft_exit(EXIT_FAILURE, W_LST_CMD), NULL);
		}			
		else if (i > 0 && el->aim == SIMPLE_CMD)
			lst_add_back(&lst_cmd, new_lst(data, i++, el->value));
		el = el->next;
	}
	return (lst_cmd);
}
