/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:38:06 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/24 09:50:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*free_strjoin(char *to_free, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(to_free, buf);
	return (free(to_free), tmp);
}

void	init_minishell(t_bigshell *data, char *env[])
{
	set_signal();
	init_env(data, env);
}

int	main(int ac, char *av[], char *env[])
{
	t_bigshell	*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	init_minishell(data, env);
	if (ac == 2)
		printf("%s\n", av[1]);
	ft_readline(data, env);
	free_all(data);
	dprintf(2, "exit status = %d\n", g_exit_status);
	return (0);
}
