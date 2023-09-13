/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:41:50 by Bea               #+#    #+#             */
/*   Updated: 2023/09/13 15:57:22 by bebigel          ###   ########.fr       */
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

int	check_tok_value(char *tok_value)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (tok_value[++i])
	{
		if (tok_value[i] == '>' || tok_value[i] == '<')
			count++;
	}
	if (count == 3 && tok_value[0] == '>')
		return (ft_error(2, W_REDIR_TWOG), count);
	else if (count == 4 && tok_value[0] == '<')
		return (ft_error(2, W_REDIR_TWOL), count);
	else if (count == 3 && tok_value[0] == '<')
		return (ft_error(2, W_REDIR_ONE), count);
	else if (count > 3 && tok_value[0] == '>')
		return (ft_error(2, W_REDIR_THREEG), count);
	else if (count > 4 && tok_value[0] == '<')
		return (ft_error(2, W_REDIR_THREEL), count);
	return (count);
}

static int	aim_redir(t_bigshell *data)
{
	t_token	*tok;
	int		count;

	tok = data->token;
	count = 0;
	while (tok != NULL)
	{
		count = check_tok_value(tok->value);
		if (count > 2)
			return (FALSE);
		if ((tok->type == LESS || tok->type == GREAT) && !tok->aim)
		{
			tok->aim = REDIR;
			if (tok->next != NULL && tok->next->type == WORD)
				tok->next->aim = REDIR;
			else if (tok->next && tok->next->next && tok->next->next->type == 1)
				tok->next->next->aim = REDIR;
			else
				return (ft_error(2, W_REDIR_ONE), FALSE);
		}
		tok = tok->next;
	}
	check_double_redir(data);
	return (TRUE);
}

void	aim_cmd(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if ((tok->value[0] == '!' || tok->value[0] == ':'
				|| tok->value[0] == '#') && !tok->value[1])
		{
			tok->aim = BLANK;
			if (tok->value[0] == '!')
				g_global.exit_status = 1;
			else
				g_global.exit_status = 0;
		}
		if (tok->type == WORD && !tok->aim)
			tok->aim = SIMPLE_CMD;
		tok = tok->next;
	}
	same_aim(data);
	add_arg_to_cmd(data);
	check_builtin(data);
}

int	parser_job(t_bigshell *data)
{
	aim_pipe(data);
	token_group(data->token);
	if (aim_redir(data) == FALSE)
		return (FALSE);
	aim_cmd(data);
	rm_blank(data);
	return (TRUE);
}
