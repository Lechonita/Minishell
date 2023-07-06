/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:41:14 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/06 17:46:23 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_simple_cmd(t_bigshell *data)
{
	// t_cmd	*simple_cmd;

	// simple_cmd = data->exec->cmd;
	print_cmd_lst(data);

}
