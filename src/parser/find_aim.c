/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_aim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:41:50 by Bea               #+#    #+#             */
/*   Updated: 2023/07/05 14:44:13 by bebigel          ###   ########.fr       */
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
			if (tok->next->next != NULL && tok->next->next->type == WORD)
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
		if ((tok->type == WORD || tok->type == INTEGER) && !tok->aim)
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

void	parser_job(t_bigshell *data)
{
	aim_redir(data);
	aim_pipe(data);
	aim_cmd(data);
	check_builtin(data);
	rm_blank(data);
	// print_t_token(data);
}