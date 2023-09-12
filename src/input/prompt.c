/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/09/12 14:48:27 by jrouillo         ###   ########.fr       */
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

void	ft_readline(t_bigshell *data, char *env[])
{
	char	*input;

	while (1)
	{
		set_signal();
		if (isatty(STDIN_FILENO))
			input = readline(PROMPT);
		if (input == NULL || !ft_strcmp(input, "exit"))
			exit_shell(NULL, data);
		set_signal_off();
		add_history(input);
		init_line(data, input);
		find_tokens(data);
		parser_job(data);
		if (simple_cmd_lst(data) == TRUE)
			executor(data, env);
		reset_prompt(data, input);
	}
	reset_prompt(data, input);
}
