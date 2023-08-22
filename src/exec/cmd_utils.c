/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:46:32 by bebigel           #+#    #+#             */
/*   Updated: 2023/08/22 10:46:35 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*new_lst(int idx, char *cmd, int builtin)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (ft_error(EXIT_FAILURE, W_MALLOC), NULL);
	new -> cmd = ft_strdup(cmd);
	if (!new -> cmd)
		return (ft_error(EXIT_FAILURE, W_LST_CMD_DUP), NULL);
	new -> cmd_arg = ft_split(cmd, ' ');
	if (!new -> cmd_arg)
		return (ft_error(EXIT_FAILURE, W_SPLIT_CMD), NULL);
	new -> idx_cmd = idx;
	new -> fd_in = 0;
	new -> fd_out = 0;
	new -> in_file = NULL;
	new -> out_file = NULL;
	if (builtin == BUILTIN)
		new -> builtin = TRUE;
	else
		new -> builtin = FALSE;
	new -> next = NULL;
	return (new);
}

static void	lst_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

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
			lst_cmd = new_lst(i++, el->value, el->aim);
		else if (i > 0 && (el->aim == SIMPLE_CMD || el->aim == BUILTIN))
			lst_add_back(&lst_cmd, new_lst(i++, el->value, el->aim));
		el = el->next;
	}
	return (lst_cmd);
}
