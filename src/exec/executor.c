/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:48:15 by Bea               #+#    #+#             */
/*   Updated: 2023/08/29 18:04:56 by Bea              ###   ########.fr       */
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

// void	ft_child(t_bigshell *data, t_simple_cmd *cmd, char *env[], int end[2])
// {
// 	int	nb_cmd;

// 	nb_cmd = g_global.nb_cmd;
// 	if (cmd->idx > 0 && dup2(cmd->fd_in, STDIN_FILENO) < 0)
// 		return (free_all(data), ft_exit(errno, strerror(errno)));
// 	close(end[0]);
// 	if (cmd->idx < nb_cmd - 1 && dup2(end[1], STDOUT_FILENO) < 0)
// 		return (free_all(data), ft_exit(errno, strerror(errno)));
// 	close(end[1]);
// 	if (cmd->idx > 0)
// 		close(cmd->fd_in);
// 	single_cmd(data, cmd, env);
// }

/*
	else if (pid == 0)
		ft_child(data, cmd, env, end);
	
	return (free_all(data), ft_exit(errno, strerror(errno)), pid);
*/

// pid_t	exec_cmd(t_bigshell *data, t_simple_cmd *cmd, char *env[], int end[2])
// {
// 	pid_t	pid;
// 	int		nb_cmd;

// 	nb_cmd = g_global.nb_cmd;
// 	pid = fork();
// 	if (pid < 0)
// 		return (free_all(data), ft_exit(errno, strerror(errno)), pid);
// 	else if (pid == 0)
// 	{
// 		dprintf(2, "\033[1;31m [%d] cmd = %10s |", cmd->idx, cmd->cmd);
// 		dprintf(2, " fdin=%2d fdout=%2d", cmd->fd_in, cmd->fd_out);
// 		dprintf(2, " end[0]=%2d end[1]=%2d\033[0m\n", end[0], end[1]);
// 		if (cmd->idx > 0 && dup2(cmd->fd_in, STDIN_FILENO) < 0)
// 			return (free_all(data), ft_exit(errno, strerror(errno)), pid);
// 		close(end[0]);
// 		if (cmd->idx < nb_cmd - 1 && dup2(end[1], STDOUT_FILENO) < 0)
// 			return (free_all(data), ft_exit(errno, strerror(errno)), pid);
// 		close(end[1]);
// 		if (cmd->idx > 0)
// 			close(cmd->fd_in);
// 		if (cmd->idx < nb_cmd - 1)
// 			close(cmd->fd_out);
// 		single_cmd(data, cmd, env);
// 	}
// 	return (pid);
// }

pid_t	exec_cmd(t_bigshell *data, t_simple_cmd *cmd, char *env[], int end[2], int start[2])
{
	pid_t	pid;
	int		nb_cmd;

	nb_cmd = g_global.nb_cmd;
	pid = fork();
	if (pid < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)), pid);
	else if (pid == 0)
	{
		dprintf(2, "\033[1;33m [%d] cmd : %7s \033[0m\n", cmd->idx, cmd->cmd);
		if (cmd->prev)
		{
			dprintf(2, "\033[1;33m if not first \033[0m\n");
			dup2(cmd->fd_in, STDIN_FILENO);
		}
		if (cmd->next)
		{
			dprintf(2, "\033[1;33m if not next \033[0m\n");
			dup2(start[0], STDIN_FILENO);
			close(cmd->next->fd_in);
		}
		close(start[0]);
		if (cmd->idx > 0)
			close(cmd->fd_in);
		if (cmd->idx < nb_cmd - 1)
			close(cmd->fd_out);
		single_cmd(data, cmd, env);
	}
	return (pid);
}

void	exec_multiple_cmd(t_bigshell *data, char *env[])
{
	t_simple_cmd	*cmd;
	pid_t			last_pid;
	int				end[2];
	int				start[2];

	cmd = data->simple_cmd;
	while (cmd)
	{
		if (cmd->prev && !cmd->prev->fd_out)
			pipe(start);
		if (cmd->next && !cmd->next->fd_in)
			pipe(end);
		last_pid = exec_cmd(data, cmd, env, start, end);
		if (cmd->prev && !cmd->prev->fd_out)
		{
			close(start[0]);
			cmd->prev->fd_out = start[1];
		}
		if (cmd->next && !cmd->next->fd_in)
		{
			close(end[1]);
			cmd->next->fd_in = end[0];
		}
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out)
			close(cmd->fd_out);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	ft_waitpid(last_pid);
}

int	executor(t_bigshell *data, char *env[])
{
	dprintf(2, "\033[3;90m in executor nb_cmd = %d\033[0m\n", g_global.nb_cmd);
	if (g_global.nb_cmd == 1 && data->simple_cmd->cmd == NULL)
		return (0);
	if (g_global.nb_cmd == 1)
		exec_simple_cmd(data, env);
	else
		exec_multiple_cmd(data, env);
	return (0);
}

/*
void	child_process(t_bigshell *data, char *env[], int pcss)
{
	t_cmd	*el;

	el = data->exec->cmd;
	handle_dup(data, pcss);
	close_pipe(data);
	while (el != NULL)
	{
		if (pcss == el->idx_cmd)
		{
			el->cmd = find_path_to_cmd(data, el->cmd_arg[0], el->cmd);
			if (el->cmd == NULL)
				error_not_found(data, CMD_NOT_FOUND, el->cmd_arg[0]);
			execve(el->cmd, el->cmd_arg, env);
			error_execve(data);
		}
		el = el->next;
	}
}

pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (free_all(data), ft_exit(errno, strerror(errno)), pid);
	else if (pid == 0)
		child_process(data, env, pcss);
	return (pid);
}

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

int	executor(t_bigshell *data, char *env[])
{
	int			nb_pro;
	pid_t		last_pid;

	nb_pro = -1;
	dprintf(2, "\033[3;90m in executor nb_cmd = %d\033[0m\n", g_global.nb_cmd);
	// data->exec = ft_calloc(1, sizeof(t_exec));
	// init_exec(data);
	if (g_global.nb_cmd == 1 && data->simple_cmd->cmd == NULL)
		return (0);
	if (g_global.nb_cmd == 1)
		exec_simple_cmd(data, env);
	else
	{
		open_pipe(data);
		while (++nb_pro < g_global.nb_cmd)
			last_pid = execute_pipex(data, env, nb_pro);
		close_pipe(data);
		ft_waitpid(last_pid);
	}
	return (0);
}
*/