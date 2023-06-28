/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/28 11:01:23 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_minishell(t_bigshell *data, char *env[])
{
	set_signal();
	init_env(data, env);
	print_strs(data->history);
	ft_readline(data);
}

int	main(int ac, char *av[], char *env[])
{
	t_bigshell	*data;
	// int			ret;

	data = ft_calloc(1, sizeof(t_bigshell));
	init_minishell(data, env);
	// display_env_struct(data);
	if (ac == 2)
		printf("%s\n", av[1]);
	// ret = ft_termcap(data);
	// printf("ret = %d\n", ret);
	ft_free_all(data);
	return (0);
}

/*
terminal capabilities :
	int			ret;
	ret = ft_termcap(data);
	printf("ret = %d\n", ret);
*/