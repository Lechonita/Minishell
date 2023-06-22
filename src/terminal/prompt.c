/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/22 17:05:37 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	catch_ctrl_d(t_bigshell *data, char *input)
{
	char	tmp[256];

	tmp[0] = 0;
	if (!data)
		return ;
	if (read(STDIN_FILENO, tmp, 0) == 0)
	{
		free(input);
		ft_putstr_fd("exit\n", 2);
		ft_free_all(data);
		exit(0);
	}
}

void	ft_readline(t_bigshell *data)
{
	char	*input;
	int		count;

	count = 0;
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
			// init_line(data, input);
			// find_tokens(data);
			count++;
		}
		free(input);
	}
	free(input);
}
