/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:37:40 by Bea               #+#    #+#             */
/*   Updated: 2023/06/30 17:25:41 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (ft_free_all(data), ft_exit(errno, strerror(errno)), pid);
	else if (pid == 0)
	{		
		handle_dup(data, pcss);
		close_pipe(data);
		while (data->history[++i])
		{
			if (pcss == data->exec->cmd->idx_cmd)
			{
				data->exec->cmd = find_path_to_cmd(data, data->history[i]);
				printf("cmd = %s\n", data->exec->cmd);
				if (data->exec->cmd == NULL)
					error_not_found(data, CMD_NOT_FOUND, data->history[i]);
				execve(data->exec->cmd, data->exec->cmd->cmd_arg, env);
				error_execve(data);
			}
		}
	}
	return (pid);
}

int	ft_waitpid(pid_t last_pid)
{
	pid_t	wpid;
	int		wstatus;
	int		return_value;

	while (1)
	{
		wpid = wait(&wstatus);
		if (wpid < 0)
			break ;
		if (wpid == last_pid)
		{
			if (WIFEXITED(wstatus))
				return_value = WEXITSTATUS(wstatus);
			else
				return_value = 128 + WTERMSIG(wstatus);
		}
	}
	return (return_value);
}

int	executor(t_bigshell *data, char *env[])
{
	int			nb_pro;
	pid_t		last_pid;

	nb_pro = -1;
	data->exec = ft_calloc(1, sizeof(t_exec));
	init_exec(data);
	open_pipe(data);
	while (++nb_pro < data->exec->nb_cmd)
		last_pid = execute_pipex(data, env, nb_pro);
	close_pipe(data);
	ft_free_all(data);
	return (ft_waitpid(last_pid));
}
