/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:45 by Bea               #+#    #+#             */
/*   Updated: 2023/08/30 17:15:20 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	error_arg_exit(char *arg)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin("Minishell: exit: ", arg);
	line = free_strjoin(tmp, ": numeric argument required\n");
	ft_putstr_fd(line, STDERR_FILENO);
	free(line);
	return (255);
}

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	determine_exit_status(t_bigshell *data, char **args)
{
	int	exit_code;

	if (!args[1])
		exit_code = 0;
	else if (is_str_digit(args[1]))
		exit_code = ft_atoi(args[1]);
	else
		exit_code = error_arg_exit(args[1]);
	free_all(data);
	exit(exit_code);
}

int	exit_shell(char **args, t_bigshell *data)
{
	ft_putendl_fd("exit by MiniShell", STDERR_FILENO);
	if (args[1] && args[2])
		return (ft_putstr_fd(W_EXIT_ARG, STDERR_FILENO), EXIT_FAILURE);
	determine_exit_status(data, args);
	return (EXIT_SUCCESS);
}
