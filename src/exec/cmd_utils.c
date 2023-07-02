/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:15:40 by Bea               #+#    #+#             */
/*   Updated: 2023/07/02 15:42:56 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static t_cmd	*new_lst(int idx, char *cmd, char **cmd_arg)
// {
// 	t_cmd	*new;

// 	new = (t_cmd *)malloc(sizeof(t_cmd));
// 	if (!new)
// 		return (NULL);
// 	new -> cmd = ft_strdup(cmd);
// 	new -> cmd_arg = cmd_arg;
// 	new -> idx_cmd = idx;
// 	new -> next = NULL;
// 	return (new);
// }

// static t_cmd	*lst_last(t_cmd *lst)
// {
// 	while (lst != NULL && lst -> next != NULL)
// 		lst = lst -> next;
// 	return (lst);
// }

// static void	lst_add_back(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*last;

// 	if (!*lst || !lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = lst_last(*lst);
// 	last -> next = new;
// }

// t_cmd	*init_cmd(t_bigshell *data)
// {
// 	t_cmd		*lst_cmd;
// 	t_token		*el;
// 	int			nb_cmd;
// 	int			i;

// 	lst_cmd = NULL;
// 	el = data->token;
// 	nb_cmd = data->exec->nb_cmd - data->exec->here_doc;
// 	i = 0;
// 	while (i < nb_cmd)
// 	{
// 		if (i == 0)
// 		{
// 			lst_cmd = new_lst(i, data->token->value);
// 			if (lst_cmd == NULL)
// 				return (NULL);
// 		}			
// 		else
// 			lst_add_back(&lst_cmd, new_lst(i, data->token->value));
// 		i++;
// 	}
// 	return (lst_cmd);
// }
