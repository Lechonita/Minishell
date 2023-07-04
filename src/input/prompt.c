/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/07/04 16:27:12 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/input.h"

void	free_readline(t_bigshell *data, char *input)
{
	free(input);
	ft_free_line(&data->line);
	ft_free_token(&data->token);
	ft_free_cmd(&data->exec->cmd);
}

void	ft_readline(t_bigshell *data, char *env[])
{
	char	*input;
	int		count;
	int		ret;

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
			init_line(data, input);
			find_tokens(data);
			ret = executor(data, env);
			dprintf(2, "_____RETOUR = %d____________________________\n", ret);
			count++;
		}
		free_readline(data, input);
	}
	free(input);
}
