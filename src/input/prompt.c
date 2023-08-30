/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/08/30 16:24:24 by bebigel          ###   ########.fr       */
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
	if (data->exec != NULL)
		ft_free_exec(&data->exec);
	if (data->in_out != NULL)
		ft_free_redirection(&data->in_out);
	if (data->simple_cmd)
		ft_free_simple_cmd(&data->simple_cmd);
}

void	simple_cmd_lst(t_bigshell *data)
{
	data->simple_cmd = init_simple_cmd();
	add_redir(data);
	add_io(data);
	merge_token_cmd(data);
	add_cmd_to_lst(data);
	print_simple_cmd(data);
}

void	ft_readline(t_bigshell *data, char *env[])
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
			catch_ctrl_d(data, input);
		add_history(input);
		init_line(data, input);
		find_tokens(data);
		parser_job(data);
		simple_cmd_lst(data);
		executor(data, env);
		reset_prompt(data, input);
	}
	reset_prompt(data, input);
}
