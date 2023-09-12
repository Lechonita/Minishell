/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:41:50 by Bea               #+#    #+#             */
/*   Updated: 2023/09/12 20:55:59 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			else if (tok->next && tok->next->next
				&& tok->next->next->type == WORD)
				tok->next->next->aim = REDIR;
			else
				ft_error(2, W_REDIR_ONE);
		}
		tok = tok->next;
	}
	check_double_redir(data);
}

void	aim_cmd(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if ((tok->value[0] == '!' || tok->value[0] == ':')
			&& !tok->value[1])
		{
			tok->aim = BLANK;
			if (tok->value[0] == '!')
				g_global.exit_status = 1;
		}
		if (tok->type == WORD && !tok->aim)
			tok->aim = SIMPLE_CMD;
		tok = tok->next;
	}
	same_aim(data);
	add_arg_to_cmd(data);
	check_builtin(data);
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

void	parser_job(t_bigshell *data)
{
	aim_pipe(data);
	token_group(data->token);
	aim_redir(data);
	aim_cmd(data);
	rm_blank(data);
}
