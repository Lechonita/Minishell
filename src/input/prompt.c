/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/07/26 17:07:26 by Bea              ###   ########.fr       */
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
		if (redir_job(data) == 1)
			executor(data, env);
		reset_prompt(data, input);
	}
	reset_prompt(data, input);
}
