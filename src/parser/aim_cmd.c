/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:47:49 by Bea               #+#    #+#             */
/*   Updated: 2023/07/03 16:33:29 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*free_strjoin(char *c, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(c, buf);
	return (free(c), tmp);
}

void	same_aim(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok->next != NULL)
	{
		if (tok->aim == tok->next->aim)
		{
			tok->value = free_strjoin(tok->value, tok->next->value);
			token_rm_next(tok);
		}
		else
			tok = tok->next;
	}
}

static char	*join_with_space(char *cmd, char *arg)
{
	char	*tmp;
	char	*cmd_arg;

	tmp = ft_strjoin(cmd, " ");
	cmd_arg = ft_strjoin(tmp, arg);
	free(cmd);
	free(tmp);
	return (cmd_arg);
}

void	add_arg_to_cmd(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok != NULL && tok->next != NULL)
	{
		if (tok->aim == SIMPLE_CMD && tok->next->type == BLANK)
		{
			while (tok->next->next && tok->next->next->aim == SIMPLE_CMD)
			{
				tok->value = join_with_space(tok->value, tok->next->next->value);
				if (tok->next->type == BLANK)
					token_rm_next(tok);
				if (tok->next->type == WORD || tok->next->type == INTEGER)
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
