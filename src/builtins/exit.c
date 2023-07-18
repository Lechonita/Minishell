/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:45 by Bea               #+#    #+#             */
/*   Updated: 2023/07/18 12:25:53 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_shell(char *cmd, char **args, t_bigshell *data)
{
	int	status;

	if (data->exit_status != NULL)
		status = ft_atoi(data->exit_status);
	else
		status = 0;
	free_all(data);
	exit(status);
	return ;
}
