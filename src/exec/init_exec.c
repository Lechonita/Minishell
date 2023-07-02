/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:25:25 by Bea               #+#    #+#             */
/*   Updated: 2023/07/02 15:42:51 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// /* presence ou non du here_doc */
// int	is_here_doc(t_bigshell *data)
// {
// 	t_token	*el;

// 	el = data->token;
// 	while (el != NULL)
// 	{
// 		if (el->token == LESSESS)
// 			return (1);
// 		el = el->next;
// 	}
// 	return (0);
// }

// /* compte le nombre de pipe donc de processus */
// int	count_cmd(t_bigshell *data)
// {
// 	int		count;
// 	t_token	*el;

// 	count = 0;
// 	el = data->token;
// 	while (el != NULL)
// 	{
// 		if (el->token == PIPE)
// 			count++;
// 		el = el->next;
// 	}
// 	return (count);
// }

// void	init_exec(t_bigshell *data)
// {
// 	data->exec->fd_in = 0;
// 	data->exec->fd_out = 0;
// 	data->exec->nb_cmd = count_cmd(data);
// 	data->exec->in_file = NULL;
// 	data->exec->out_file = NULL;
// 	data->exec->here_doc = is_here_doc(data);
// 	data->exec->cmd = init_cmd(data);
// 	if (data->exec->cmd == NULL)
// 		return (ft_free_all(data), ft_exit(EXIT_FAILURE, W_LST_CMD));

// }
