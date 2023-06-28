/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/28 17:42:18 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	save_line_for_test(t_bigshell *data, char *input, int count)
{
	if (!data)
		return ;
	data->history[count] = ft_strdup(input);
	if (!data->history[count])
		ft_exit(EXIT_FAILURE, "strdup in save line for test error\n");
}

void	ft_readline(t_bigshell *data)
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
			// find_tokens(data);
			count++;
		}
		free(input);
		ft_free_line(&data->line);
	}
	free(input);
}
