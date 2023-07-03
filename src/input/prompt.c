/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/07/03 17:33:11 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/input.h"

void	save_line_for_test(t_bigshell *data, char *input, int count)
{
	if (!data)
		return ;
	data->history[count] = ft_strdup(input);
	if (!data->history[count])
		ft_exit(EXIT_FAILURE, "strdup in save line for test error\n");
}

void	free_readline(t_bigshell *data, char *input)
{
	free(input);
	ft_free_line(&data->line);
	ft_free_token(&data->token);
}

void	ft_readline(t_bigshell *data, char *env[])
{
	char	*input;
	int		count;

	count = 0;
	data->history = ft_calloc(50, sizeof(char *));
	while (1)
	{
		input = readline("$ ");
		if (input == NULL)
			catch_ctrl_d(data, input);
		if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
			break ;
		if (input != NULL)
		{
			add_history(input);
			save_line_for_test(data, input, count);
			init_line(data, input);
			find_tokens(data);
			executor(data, env);
			count++;
		}
		free_readline(data, input);
	}
	free(input);
}
