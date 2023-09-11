/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:38:06 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/11 22:01:13 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_global	g_global;

char	*free_strjoin(char *to_free, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(to_free, buf);
	return (free(to_free), tmp);
}

void	init_minishell(t_bigshell *data, char *env[])
{
	locate_shell(data, 1);
	init_env(data, env);
	g_global.exit_status = 0;
	g_global.nb_cmd = 0;
	g_global.heredoc = 0;
}

int	main(int ac, char *av[], char *env[])
{
	t_bigshell	*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	init_minishell(data, env);
	if (ac == 2)
		printf("%s\n", av[1]);
	ft_readline(data, data->env_paths);
	free_all(data);
	return (g_global.exit_status);
}
