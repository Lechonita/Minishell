/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:46:11 by bebigel           #+#    #+#             */
/*   Updated: 2023/08/22 13:40:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_dup_simp_cmd(t_simple_cmd *simple_cmd, int red)
{
	if ((simple_cmd->fd_in < 3 && (red == 0 || red == 2))
		|| (simple_cmd->fd_out < 3 && (red == 0 || red == 1)))
		return ;
	if (red == 1)
		dup2(simple_cmd->fd_out, STDOUT_FILENO);
	else if (red == 2)
		dup2(simple_cmd->fd_in, STDIN_FILENO);
	else if (red == 0)
	{
		dup2(simple_cmd->fd_out, STDOUT_FILENO);
		dup2(simple_cmd->fd_in, STDIN_FILENO);
	}
	if (simple_cmd->fd_in)
		close(simple_cmd->fd_in);
	if (simple_cmd->fd_out)
		close(simple_cmd->fd_out);
}

int	find_cmd(t_bigshell *data, t_simple_cmd *simple_cmd, char *env[])
{
	simple_cmd->cmd = find_path_to_cmd(data, simple_cmd->cmd_arg[0],
			simple_cmd->cmd);
	if (simple_cmd->cmd == NULL)
		return (msg_not_found(CMD_NOT_FOUND, simple_cmd->cmd_arg[0]));
	execve(simple_cmd->cmd, simple_cmd->cmd_arg, env);
	error_execve(data);
	return (EXIT_FAILURE);
}

void	handle_simple_cmd(t_bigshell *data, char *env[])
{
	t_simple_cmd	*simple_cmd;
	int				ret;

	ret = 0;
	simple_cmd = data->simple_cmd;
	handle_dup_simp_cmd(simple_cmd, simple_cmd->redir_or_not);
	if (simple_cmd->builtin != 0)
		ret = exec_builtin_cmd(data, simple_cmd->cmd, simple_cmd->cmd_arg);
	else if (simple_cmd->cmd_arg[0][0] != '\0')
		ret = find_cmd(data, simple_cmd, env);
	free_all(data);
	exit(ret);
}

int	exec_simple_cmd(t_bigshell *data, char *env[])
{
	pid_t			pid;
	int				status;
	t_simple_cmd	*cmd;

	cmd = data->simple_cmd;
	if (!ft_strcmp(cmd->cmd_arg[0], "exit") || !ft_strcmp(cmd->cmd_arg[0], "cd")
		|| !ft_strcmp(cmd->cmd_arg[0], "export")
		|| !ft_strcmp(cmd->cmd_arg[0], "unset"))
	{
		g_global.exit_status = exec_builtin_no_fork(data, cmd->cmd,
				cmd->cmd_arg);
		return (1);
	}
	pid = fork();
	if (pid < 0)
		return (ft_error(errno, strerror(errno)), errno);
	else if (pid == 0)
		handle_simple_cmd(data, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.exit_status = WTERMSIG(status) + 128;
	return (1);
}
