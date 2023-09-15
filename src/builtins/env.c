/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:40 by Bea               #+#    #+#             */
/*   Updated: 2023/09/15 14:54:28 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*join_for_env(char *name, char *value)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(name, "=");
	line = free_strjoin(tmp, value);
	return (line);
}

int	print_env(t_bigshell *data, char *cmd, char **args, int fd_out)
{
	t_env	*el;
	char	*to_print;

	(void)cmd;
	if (args[1] != NULL)
		return (ft_error(1, W_BUILT_ENV), EXIT_FAILURE);
	el = data->env;
	while (el)
	{
		to_print = join_for_env(el->name, el->value);
		if (el->to_export == FALSE)
			ft_putendl_fd(to_print, fd_out);
		free(to_print);
		el = el->next;
	}
	return (EXIT_SUCCESS);
}
