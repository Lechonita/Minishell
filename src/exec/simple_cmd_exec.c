/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:46:11 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/11 16:09:37 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	close_fd_redir(t_simple_cmd *simple_cmd)
{
	t_redir	*red;

	red = simple_cmd->redir;
	while (red)
	{
		if (red->fd > 2)
			close(red->fd);
		red = red->next;
	}
}

static void	handle_fds(t_bigshell *data, t_simple_cmd *simple_cmd)
{
	t_simple_cmd	*el;

	el = data->simple_cmd;
	if ((simple_cmd->fd_in < 3 && simple_cmd->in_file != NULL)
		|| (simple_cmd->fd_out < 3 && simple_cmd->out_file != NULL))
		return ;
	if (simple_cmd->fd_out > 2 && dup2(simple_cmd->fd_out, STDOUT_FILENO) < 0)
		dprintf(2, "\033[1;31m error out \033[0m");
	if (simple_cmd->fd_in > 2 && dup2(simple_cmd->fd_in, STDIN_FILENO) < 0)
		dprintf(2, "\033[1;31m error in \033[0m]");
	while (el)
	{
		if (el->fd_in > 2)
			close(el->fd_in);
		if (el->fd_out > 2)
			close(el->fd_out);
		if (el->end[0])
			close(el->end[0]);
		if (el->end[1])
			close(el->end[1]);
		if (el->redir)
			close_fd_redir(el);
		el = el->next;
	}
}

static int	find_cmd(t_bigshell *data, t_simple_cmd *simple_cmd, char *env[])
{
	simple_cmd->cmd = find_path_to_cmd(data, simple_cmd->cmd_arg[0],
			simple_cmd->cmd);
	if (simple_cmd->cmd == NULL)
		return (msg_not_found(CMD_NOT_FOUND, simple_cmd->cmd_arg[0]));
	if (simple_cmd->cmd[0] == '/' && (!simple_cmd->cmd[1]
			|| simple_cmd->cmd[1] == ' ' || simple_cmd->cmd[1] == '/'
			|| simple_cmd->cmd[1] == '.'))
		return (is_directory(simple_cmd->cmd, IS_DIRECTORY));
	execve(simple_cmd->cmd, simple_cmd->cmd_arg, env);
	error_execve(data);
	return (EXIT_FAILURE);
}

void	single_cmd(t_bigshell *data, t_simple_cmd *simple_cmd, char *env[])
{
	int	ret;

	ret = 0;
	handle_fds(data, simple_cmd);
	if (simple_cmd->builtin != 0)
		ret = exec_builtin_cmd(data, simple_cmd->cmd, simple_cmd->cmd_arg);
	else if (simple_cmd->cmd == NULL)
		ret = 0;
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
		single_cmd(data, cmd, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.exit_status = WTERMSIG(status) + 128;
	return (1);
}
