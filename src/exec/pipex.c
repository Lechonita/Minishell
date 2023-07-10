/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:37:40 by Bea               #+#    #+#             */
/*   Updated: 2023/07/07 10:28:37 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

/* dprintf(2, "cmd = %s\n", el->cmd); */
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
			el->cmd = find_path_to_cmd(data, el->cmd_arg[0]);
			if (el->cmd == NULL)
				error_not_found(data, CMD_NOT_FOUND, el->cmd_arg[0]);
			print_cmd_lst(data);
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
	if (data->exec->nb_cmd == 1)
		last_pid = exec_simple_cmd(data, env);
	else
	{
		open_pipe(data);
		while (++nb_pro < data->exec->nb_cmd)
			last_pid = execute_pipex(data, env, nb_pro);
		close_pipe(data);
	}
	return (ft_waitpid(last_pid));
}
