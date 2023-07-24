/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:30 by Bea               #+#    #+#             */
/*   Updated: 2023/07/20 16:30:33 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_echo(char *cmd, char **args)
{
	int	i;

	i = 1;
	(void)cmd;
	while (args[i])
	{
		if (i == 1 && args[i][0] == '-' && args[i][1] == 'n'
			&& args[i][2] == '\0')
			i++;
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (args[1] && args[1][0] == '-' && args[1][1] == 'n' && args[1][2] == '\0')
		return (EXIT_SUCCESS);
	printf("\n");
	return (EXIT_SUCCESS);
}
