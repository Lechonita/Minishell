/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:46:11 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/24 15:39:47 by bebigel          ###   ########.fr       */
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

int	find_cmd(t_bigshell *data, t_cmd *simple_cmd, char *env[])
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
	t_cmd	*simple_cmd;
	int		ret;

	ret = 0;
	simple_cmd = data->exec->cmd;
	handle_dup_simp_cmd(data);
	if (simple_cmd->builtin != 0)
	{
		ret = exec_builtin_cmd(data, simple_cmd->cmd, simple_cmd->cmd_arg);
		free_all(data);
		exit(ret);
	}
	else if (simple_cmd->cmd_arg[0][0] != '\0')
		ret = find_cmd(data, simple_cmd, env);
	free_all(data);
	exit(ret);
}

void	exec_simple_cmd(t_bigshell *data, char *env[])
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	if (data->exec->cmd == NULL)
		return ;
	cmd = data->exec->cmd;
	if (!ft_strncmp(cmd->cmd_arg[0], "exit", ft_strlen("exit"))
		|| !ft_strncmp(cmd->cmd_arg[0], "cd", ft_strlen("cd"))
		|| !ft_strncmp(cmd->cmd_arg[0], "export", ft_strlen("export"))
		|| !ft_strncmp(cmd->cmd_arg[0], "unset", ft_strlen("unset")))
	{
		g_exit_status = exec_builtin_no_fork(data, cmd->cmd, cmd->cmd_arg);
		return ;
	}
	pid = fork();
	if (pid < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)));
	if (pid == 0)
		handle_simple_cmd(data, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
}
