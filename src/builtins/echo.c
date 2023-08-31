/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:30 by Bea               #+#    #+#             */
/*   Updated: 2023/07/26 14:52:08 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_input(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	print_echo(char *cmd, char **args)
{
	int	i;
	int	j;
	int	n_nb;

	i = 1;
	n_nb = 0;
	(void)cmd;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			n_nb++;
		else
			break ;
		i++;
	}
	print_input(args, i);
	if (n_nb == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
