/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:32 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/21 12:27:44 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin_cmd(t_bigshell *data, char *cmd, char **args)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		print_echo(NULL, args);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		print_env(data);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		print_working_directory(data);
	else
		return (FALSE);
	return (TRUE);
}

int	exec_builtin_no_fork(t_bigshell *data, char *cmd, char **args)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		ret = exit_shell(args, data);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		ret = change_directory(args, data);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		ret = export_var(cmd, args, data);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		ret = unset_var(NULL, args, data);
	dprintf(2, "ret = %d\n", ret);
	return (ret);
}
