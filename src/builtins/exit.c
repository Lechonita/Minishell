/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:45 by Bea               #+#    #+#             */
/*   Updated: 2023/07/18 19:38:35 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_shell(char *cmd, char **args, t_bigshell *data)
{
	int	status;

	(void)cmd;
	(void)args;
	status = data->exit_status;
	free_all(data);
	exit(status);
	return ;
}
