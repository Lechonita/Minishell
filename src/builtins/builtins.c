/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:32 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/13 14:27:52 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin_cmd(t_bigshell *data, char *cmd, char **args)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		print_echo(data, NULL, args);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		print_env(data, cmd, args);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		print_working_directory(data);
	else
		return (FALSE);
	return (TRUE);
}

int	exec_builtin_no_fork(t_bigshell *data, char *cmd, char **args)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		ret = exit_shell(args, data);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		ret = change_directory(args, data);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		ret = export_var(args, data);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		ret = unset_var(args, data);
	return (ret);
}
