/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:57 by Bea               #+#    #+#             */
/*   Updated: 2023/09/06 17:12:35 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_working_directory(t_bigshell *data)
{
	char	*cwd;
	char	*dir;

	dir = get_env_value(data, "PWD");
	if (!dir)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (free_all(data),
				ft_exit(errno, strerror(errno)), EXIT_FAILURE);
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		printf("%s\n", dir);
	return (EXIT_SUCCESS);
}
