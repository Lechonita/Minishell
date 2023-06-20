/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/20 17:07:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_save_history(t_bigshell *data, char *input, int count)
{
	if (!data || !input)
		return ;
	data->history[count] = ft_strdup(input);
	if (!data->history[count])
		return ;
}

void	ft_readline(t_bigshell *data)
{
	char	*input;
	int		count;

	count = 0;
	data->history = ft_calloc(50, sizeof(char *));
	// block_signal(SIGQUIT);
	set_signal();
	while (1)
	{
		input = readline(">> ");
		if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			ft_save_history(data, input, count);
			count++;
		}
		free(input);
	}
	free(input);
}

