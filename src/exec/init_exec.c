/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:25:25 by Bea               #+#    #+#             */
/*   Updated: 2023/07/03 17:42:21 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* presence ou non du here_doc */
int	is_here_doc(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if (ft_strncmp(tok->value, "<<", ft_strlen("<<")) == 0)
			return (1);
		tok = tok->next;
	}
	return (0);
}

/* compte le nombre de pipe donc de processus */
int	count_cmd(t_bigshell *data)
{
	int		count;
	t_token	*el;

	count = 0;
	el = data->token;
	while (el != NULL)
	{
		if (el->type == PIPE)
			count++;
		el = el->next;
	}
	return (count);
}

void	init_exec(t_bigshell *data)
{
	data->exec->fd_in = 0;
	data->exec->fd_out = 0;
	data->exec->nb_cmd = count_cmd(data) + 1;
	data->exec->in_file = NULL;
	data->exec->out_file = NULL;
	data->exec->here_doc = is_here_doc(data);
	data->exec->cmd = init_cmd(data);
	if (data->exec->cmd == NULL)
		return (ft_free_all(data), ft_exit(EXIT_FAILURE, W_LST_CMD));

}
