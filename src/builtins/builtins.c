/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:32 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/19 17:13:54 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin_cmd(t_bigshell *data, char *cmd, char **args)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		print_echo(NULL, args);
	// else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
	// 	change_directory(args, data);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		print_env(data);
	// else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
	// 	exit_shell(NULL, args, data);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		export_var(cmd, args, data);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		print_working_directory(data);
	// else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
	// 	unset_var(NULL, args, data);
	else
		return (FALSE);
	return (TRUE);
}
