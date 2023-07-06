/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:25:25 by Bea               #+#    #+#             */
/*   Updated: 2023/07/06 17:50:57 by bebigel          ###   ########.fr       */
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

char	*in_file_path(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok->next != NULL)
	{
		if (tok->type == LESS && tok->next->type == WORD)
			return (tok->next->value);
		tok = tok->next;
	}
	return (NULL);
}

char	*out_file_path(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok->next != NULL)
	{
		if (tok->type == GREAT && tok->next->type == WORD)
			return (tok->next->value);
		tok = tok->next;
	}
	return (NULL);
}

void	init_exec(t_bigshell *data)
{
	data->exec->here_doc = is_here_doc(data);
	data->exec->in_file = in_file_path(data);
	data->exec->out_file = out_file_path(data);
	redir_in_file(data);
	redir_out_file(data);
	data->exec->nb_cmd = count_cmd(data) + 1;
	dprintf(2, "nb_cmd = %d\n", data->exec->nb_cmd);
	data->exec->cmd = init_cmd(data);
	if (data->exec->nb_cmd == 1)
		exec_simple_cmd(data);
}
