/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:41:14 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/12 15:47:57 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_dup_simp_cmd(t_bigshell *data)
{
	int	red;

	red = data->exec->no_redir;
	if ((data->exec->fd_in < 3 && (red == 0 || red == 2))
		|| (data->exec->fd_out < 3 && (red == 0 || red == 1)))
		return (free_all(data), exit(EXIT_FAILURE));
	if (red == 1)
		dup2(data->exec->fd_out, STDOUT_FILENO);
	else if (red == 2)
		dup2(data->exec->fd_in, STDIN_FILENO);
	else if (red == 0)
	{
		dup2(data->exec->fd_out, STDOUT_FILENO);
		dup2(data->exec->fd_in, STDIN_FILENO);
	}
}

pid_t	exec_simple_cmd(t_bigshell *data, char *env[])
{
	t_cmd	*simple_cmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)), pid);
	else if (pid == 0)
	{
		simple_cmd = data->exec->cmd;
		handle_dup_simp_cmd(data);
		simple_cmd->cmd = find_path_to_cmd(data, simple_cmd->cmd_arg[0],
				simple_cmd->cmd);
		if (simple_cmd->cmd == NULL)
			error_not_found(data, CMD_NOT_FOUND, simple_cmd->cmd_arg[0]);
		execve(simple_cmd->cmd, simple_cmd->cmd_arg, env);
		error_execve(data);
	}
	return (pid);
}
