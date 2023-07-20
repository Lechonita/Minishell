/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:45 by Bea               #+#    #+#             */
/*   Updated: 2023/07/20 19:11:07 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exit_shell(char *cmd, char **args, t_bigshell *data)
{
	int	status;

	(void)cmd;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && args[2])
		return (ft_putstr_fd(W_EXIT_ARG, STDERR_FILENO), EXIT_FAILURE);
	status = data->exit_status;
	free_all(data);
	exit(status);
	return (EXIT_SUCCESS);
}
