/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:32 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/15 14:48:39 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_bigshell *data, char *cmd, char **args, int fd_out)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		ret = print_echo(data, NULL, args, fd_out);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		ret = print_env(data, cmd, args, fd_out);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		ret = print_working_directory(data, fd_out);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		ret = exit_shell(args, data);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		ret = change_directory(args, data);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		ret = export_var(args, data, fd_out);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		ret = unset_var(NULL, args, data);
	else
		return (FALSE);
	return (ret);
}
