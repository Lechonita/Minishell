/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:47:49 by Bea               #+#    #+#             */
/*   Updated: 2023/08/29 15:01:02 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

void	same_aim(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok->next != NULL)
	{
		if (tok->aim == tok->next->aim && tok->aim != REDIR)
		{
			tok->value = freejoin(tok->value, tok->next->value);
			token_rm_next(tok);
		}
		else
			tok = tok->next;
	}
}

char	*def_tok_value(char *value, char *next, char *nextnext)
{
	if (!value && !next && !nextnext)
		return (NULL);
	else if (!value)
		return (nextnext);
	else if (!nextnext)
		return (value);
	if (last_is_dollar(value) == 1 && is_blank(next[0]) == 0)
		return (freejoin(value, nextnext));
	return (join_spac(value, nextnext, " "));
}

void	add_arg_to_cmd(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL && tok->next != NULL)
	{
		if (tok->aim == SIMPLE_CMD && (tok->next->type == BLANK
				|| tok->next->type == SQUOTE || tok->next->type == DQUOTE))
		{
			while (tok->next->next && tok->next->next->aim == SIMPLE_CMD)
			{
				tok->value = def_tok_value(tok->value, tok->next->value,
						tok->next->next->value);
				if (tok->next->type == BLANK
					|| (tok->next->type == SQUOTE || tok->next->type == DQUOTE))
					token_rm_next(tok);
				if (tok->next->type == WORD)
					token_rm_next(tok);
				if (tok->next == NULL)
					break ;
			}
		}
		tok = tok->next;
	}
}

void	check_builtin(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if (ft_strncmp(tok->value, "echo", ft_strlen("echo")) == 0
			|| ft_strncmp(tok->value, "cd", ft_strlen("cd")) == 0
			|| ft_strncmp(tok->value, "pwd", ft_strlen("pwd")) == 0
			|| ft_strncmp(tok->value, "export", ft_strlen("export")) == 0
			|| ft_strncmp(tok->value, "unset", ft_strlen("unset")) == 0
			|| ft_strncmp(tok->value, "env", ft_strlen("env")) == 0
			|| ft_strncmp(tok->value, "exit", ft_strlen("exit")) == 0)
			tok->aim = BUILTIN;
		tok = tok->next;
	}
}

void	check_double_redir(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL)
	{
		if (ft_strncmp(tok->value, "<<", 2) == 0)
			tok->type = DLESS;
		else if (ft_strncmp(tok->value, ">>", 2) == 0)
			tok->type = DGREAT;
		tok = tok->next;
	}
}
