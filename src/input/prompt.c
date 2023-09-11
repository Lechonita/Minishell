/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/09/11 14:33:02 by jrouillo         ###   ########.fr       */
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
}

void	simple_cmd_lst(t_bigshell *data)
{
	data->simple_cmd = init_simple_cmd();
	add_redir(data);
	add_io(data);
	merge_token_cmd(data);
	add_cmd_to_lst(data);
}

void	ft_readline(t_bigshell *data, char *env[])
{
	char	*input;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline(PROMPT);
		if (input == NULL)
			catch_ctrl_d(data, input);
		add_history(input);
		init_line(data, input);
		// print_t_line(data->line);
		find_tokens(data);
		parser_job(data);
		// print_t_token(data);
		simple_cmd_lst(data);
		// print_simple_cmd(data);
		executor(data, env);
		reset_prompt(data, input);

	}
	reset_prompt(data, input);
}
