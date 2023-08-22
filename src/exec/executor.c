/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:48:15 by Bea               #+#    #+#             */
/*   Updated: 2023/08/22 13:40:53 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
