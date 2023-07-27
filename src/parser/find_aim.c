/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_aim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:41:50 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 18:54:16 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	aim_redir(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if ((tok->type == LESS || tok->type == GREAT) && !tok->aim)
		{
			tok->aim = REDIR;
			if (tok->next != NULL && tok->next->type == WORD)
				tok->next->aim = REDIR;
			else if (tok->next->next != NULL && tok->next->next->type == WORD)
				tok->next->next->aim = REDIR;
		}
		tok = tok->next;
	}
}

void	aim_pipe(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if (tok->type == PIPE && !tok->aim)
			tok->aim = PIPEX;
		tok = tok->next;
	}
}

void	aim_cmd(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if (tok->type == WORD && !tok->aim)
			tok->aim = SIMPLE_CMD;
		tok = tok->next;
	}
	same_aim(data);
	add_arg_to_cmd(data);
}

void	rm_blank(t_bigshell *data)
{
	t_token	*tok;

	if (!data->token || !data->token->next)
		return ;
	tok = data->token;
	while (tok != NULL && tok->next != NULL)
	{
		if (tok->next->type == BLANK)
			token_rm_next(tok);
		tok = tok->next;
	}
}

int	count_aim(t_bigshell *data, int type)
{
	t_token	*tok;
	int		count;

	tok = data->token;
	count = 0;
	while (tok != NULL)
	{
		if (tok->aim == type)
			count++;
		tok = tok->next;
	}
	return (count);
}

void	merge_token_cmd(t_bigshell *data)
{
	t_token	*tok;
	int		group;
	int		count;

	tok = data->token;
	group = 0;
	while (group < g_global.nb_cmd)
	{
		count = 0;
		while (tok != NULL && tok->group != group)
			tok = tok->next;
		count = count_aim(data, SIMPLE_CMD) + count_aim(data, BUILTIN);
		if (count > 1)
			dprintf(2, "count_aim(data, WORD) = %d group = %d\n",
				count, group);
		group++;
	}
}

void	parser_job(t_bigshell *data)
{
	aim_redir(data);
	aim_pipe(data);
	aim_cmd(data);
	check_builtin(data);
	check_double_redir(data);
	rm_blank(data);
	token_group(data->token);
	merge_token_cmd(data);
	data->simple_cmd = init_simple_cmd();
	add_redir_to_cmd(data);
	add_in_out_to_cmd(data);
	print_simple_cmd(data);
}
