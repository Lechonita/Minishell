/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:34:26 by lechon            #+#    #+#             */
/*   Updated: 2023/06/23 17:12:09 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*handle_good_path(t_bigshell *data, char *command)
{
	if (access(command, F_OK & X_OK) == 0)
		return (command);
	else if (access(command, F_OK) < 0)
		error_not_found(data, FILE_NOT_FOUND, command);
	else if (access(command, X_OK) < 0)
		error_not_found(data, CMD_NOT_FOUND, command);
	return (NULL);
}

char	*find_path_to_cmd(t_bigshell *data, char *cmd)
{
	char	*tmp_path;
	char	*command;
	int		i;

	i = -1;
	if (data->env->env_paths == NULL && ft_strchr(cmd, '/') == NULL)
		error_not_found(data, FILE_NOT_FOUND, cmd);
	if (ft_strchr(cmd, '/') != NULL)
		command = handle_good_path(data, cmd);
	while (data->env->env_paths[++i])
	{
		tmp_path = ft_strjoin(data->env->env_paths[i], "/");
		command = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(command, F_OK & X_OK) == 0)
			return (command);
		free(command);
	}
	return (NULL);
}

/*	
in child process:	
	handle_dup(data, pcss);
	close_pipe(data);
	while (el)
	{
		if (pcss == el->idx_cmd)
		{
			el->cmd = find_path_to_cmd(data, el->cmd_arg[0]);
			if (el->cmd == NULL)
				error_not_found(data, CMD_NOT_FOUND, el->cmd_arg[0]);
			execve(el->cmd, el->cmd_arg, env);
			error_execve(data);
		}
		el = el->next;
	}

*/

void	get_path(t_bigshell *data)
{
    t_env	*tmp;

    tmp = data->env;
    while (tmp)
    {
        if (ft_strncmp(tmp->name, "PATH", 4) == 0)
        {
            tmp->env_paths = ft_split(tmp->value, ':');
			print_strs(tmp->env_paths);
			if (!tmp->env_paths)
				return (ft_free_all(data), ft_exit(EXIT_FAILURE, W_SPLIT_ENV));
        }
        tmp = tmp->next;
    }
    return ;
}
