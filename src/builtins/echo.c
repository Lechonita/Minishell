/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:30 by Bea               #+#    #+#             */
/*   Updated: 2023/09/18 14:53:56 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_input(char **args, int i, int fd_out)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
}

int	print_echo(t_bigshell *data, char *cmd, char **args, int fd_out)
{
	int	i;
	int	j;
	int	n_nb;

	i = 1;
	n_nb = 0;
	(void)cmd;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) != 0)
		error_not_found(data, CMD_NOT_FOUND, args[0]);
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			n_nb++;
		else
			break ;
		i++;
	}
	print_input(args, i, fd_out);
	if (n_nb == 0)
		write(fd_out, "\n", 1);
	return (EXIT_SUCCESS);
}
