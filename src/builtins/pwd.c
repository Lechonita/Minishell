/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:57 by Bea               #+#    #+#             */
/*   Updated: 2023/09/15 14:56:37 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_working_directory(t_bigshell *data, int fd_out)
{
	char	*cwd;
	char	*dir;

	dir = get_env_value(data, "PWD");
	if (!dir)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (free_all(data),
				ft_error(errno, strerror(errno)), EXIT_FAILURE);
		ft_putendl_fd(cwd, fd_out);
		free(cwd);
	}
	else
		ft_putendl_fd(dir, fd_out);
	return (EXIT_SUCCESS);
}
