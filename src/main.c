/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:38:06 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/12 15:29:56 by bebigel          ###   ########.fr       */
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

void	cpy_env(t_bigshell *data, char *env[])
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (env[len])
		len++;
	data->env_cpy = ft_calloc(len + 1, sizeof(char *));
	while (env[++i])
		data->env_cpy[i] = ft_strdup(env[i]);
	data->env_cpy[i] = NULL;
}

static void	init_minishell(t_bigshell *data)
{
	locate_shell(data, 1);
	init_env(data, data->env_cpy);
	g_global.exit_status = 0;
	g_global.nb_cmd = 0;
	g_global.heredoc = 0;
}

int	main(int ac, char *av[], char *env[])
{
	t_bigshell	*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	cpy_env(data, env);
	init_minishell(data);
	if (ac == 2)
		printf("%s\n", av[1]);
	ft_readline(data);
	free_all(data);
	return (g_global.exit_status);
}
