/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/09/13 19:01:33 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reset_prompt(t_bigshell *data, char *input)
{
	if (input != NULL)
		free(input);
	if (data->line != NULL)
		ft_free_line(&data->line);
	if (data->token != NULL)
		ft_free_token(&data->token);
	if (data->simple_cmd)
		ft_free_simple_cmd(&data->simple_cmd);
	if (g_global.heredoc == 1)
		unlink("minishell_here_doc");
}

void	add_cmd_to_lst_norm(t_token *tok, t_simple_cmd *cmd)
{
	cmd->cmd = ft_strdup(tok->value);
	if (!cmd->cmd)
		ft_error(EXIT_FAILURE, W_LST_CMD_DUP);
	if (tok->quote_flag == 0)
		cmd->cmd_arg = ft_split(tok->value, ' ');
	else
		cmd->cmd_arg = ft_split(tok->value, '\n');
	if (!cmd->cmd_arg)
		ft_error(EXIT_FAILURE, W_SPLIT_CMD);
	if (tok->aim == BUILTIN)
		cmd->builtin = 1;
}

void	add_cmd_to_lst(t_bigshell *data)
{
	t_token			*tok;
	t_simple_cmd	*simple_cmd;

	simple_cmd = data->simple_cmd;
	while (simple_cmd != NULL)
	{
		tok = data->token;
		while (tok)
		{
			if ((tok->aim == SIMPLE_CMD || tok->aim == BUILTIN)
				&& tok->group == simple_cmd->idx)
				add_cmd_to_lst_norm(tok, simple_cmd);
			tok = tok->next;
		}
		simple_cmd = simple_cmd->next;
	}
}

static int	simple_cmd_lst(t_bigshell *data)
{
	data->simple_cmd = init_simple_cmd();
	if (add_redir(data) == FALSE)
		return (FALSE);
	add_io(data);
	merge_token_cmd(data);
	add_cmd_to_lst(data);
	return (TRUE);
}

void	ft_readline(t_bigshell *data)
{
	char	*input;

	while (1)
	{
		set_signal();
		if (isatty(STDIN_FILENO))
			input = readline(PROMPT);
		if (input == NULL || !ft_strcmp(input, "exit"))
			exit_shell(NULL, data);
		add_history(input);
		if (init_line(data, input) == TRUE)
		{
			find_tokens(data);
			if (parser_job(data) == TRUE && simple_cmd_lst(data) == TRUE)
				executor(data, data->env_cpy);
		}
		reset_prompt(data, input);
	}
	reset_prompt(data, input);
}
