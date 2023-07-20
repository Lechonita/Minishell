/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:41:14 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/20 19:08:36 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_dup_simp_cmd(t_bigshell *data)
{
	int	red;

	red = data->redir_or_not;
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
	if (data->exec->fd_in)
		close(data->exec->fd_in);
	if (data->exec->fd_out)
		close(data->exec->fd_out);
}

void	handle_simple_cmd(t_bigshell *data, char *env[])
{
	t_cmd	*simple_cmd;

	if (data->exec->cmd != NULL)
	{
		simple_cmd = data->exec->cmd;
		handle_dup_simp_cmd(data);
		if (simple_cmd->builtin == 0)
		{
			simple_cmd->cmd = find_path_to_cmd(data, simple_cmd->cmd_arg[0],
				simple_cmd->cmd);
			if (simple_cmd->cmd == NULL)
				error_not_found(data, CMD_NOT_FOUND, simple_cmd->cmd_arg[0]);
			execve(simple_cmd->cmd, simple_cmd->cmd_arg, env);
			error_execve(data);
		}
		else
			exec_builtin_cmd(data, simple_cmd->cmd, simple_cmd->cmd_arg);
	}
	return ;
}

pid_t	exec_simple_cmd(t_bigshell *data, char *env[])
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = data->exec->cmd;
	if (!ft_strncmp(cmd->cmd_arg[0], "exit", ft_strlen("exit"))
		|| !ft_strncmp(cmd->cmd_arg[0], "cd", ft_strlen("cd"))
		|| !ft_strncmp(cmd->cmd_arg[0], "export", ft_strlen("export"))
		|| !ft_strncmp(cmd->cmd_arg[0], "unset", ft_strlen("unset")))
		return (exec_builtin_no_fork(data, cmd->cmd, cmd->cmd_arg));
	pid = fork();
	if (pid < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)), pid);
	else if (pid == 0)
		handle_simple_cmd(data, env);
	return (pid);
}
