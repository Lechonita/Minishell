/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:48:15 by Bea               #+#    #+#             */
/*   Updated: 2023/09/12 14:36:36 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_waitpid(pid_t last_pid)
{
	pid_t	wpid;
	int		wstatus;

	while (1)
	{
		wpid = wait(&wstatus);
		if (wpid < 0)
			break ;
		if (wpid == last_pid)
		{
			if (WIFEXITED(wstatus))
				g_global.exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				g_global.exit_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (0);
}

pid_t	exec_cmd(t_bigshell *data, t_simple_cmd *cmd, char *env[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)), pid);
	else if (pid == 0)
		single_cmd(data, cmd, env);
	return (pid);
}

void	exec_multiple_cmd(t_bigshell *data, char *env[])
{
	t_simple_cmd	*cmd;
	pid_t			last_pid;

	cmd = data->simple_cmd;
	while (cmd)
	{
		if (cmd->next && (!cmd->next->fd_in || !cmd->fd_out))
		{
			pipe(cmd->end);
			if (!cmd->next->fd_in)
				cmd->next->fd_in = cmd->end[0];
			if (!cmd->fd_out)
				cmd->fd_out = cmd->end[1];
		}
		last_pid = exec_cmd(data, cmd, env);
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out)
			close(cmd->fd_out);
		if (cmd->end[1])
			close(cmd->end[1]);
		cmd = cmd->next;
	}
	ft_waitpid(last_pid);
}

int	executor(t_bigshell *data, char *env[])
{
	if (g_global.nb_cmd == 1 && data->simple_cmd->cmd == NULL)
		return (0);
	if (g_global.nb_cmd == 1)
		exec_simple_cmd(data, env);
	else
		exec_multiple_cmd(data, env);
	return (0);
}
