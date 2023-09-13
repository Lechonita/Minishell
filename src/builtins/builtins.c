/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:32 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/13 15:41:55 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_bigshell *data, char *cmd, char **args)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		ret = print_echo(data, NULL, args);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		ret = print_env(data, cmd, args);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		ret = print_working_directory(data);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		ret = exit_shell(args, data);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		ret = change_directory(args, data);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		ret = export_var(args, data);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		ret = unset_var(args, data);
	else
		return (FALSE);
	return (ret);
}
