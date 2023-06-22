/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/22 18:19:55 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_bigshell	*data;
	// int			ret;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	init_env(data, env);
	set_signal();
	ft_readline(data);
	if (ac == 2)
		printf("%s\n", av[1]);
	// ret = ft_termcap(data);
	// printf("ret = %d\n", ret);
	ft_free_all(data);
	return (0);
}

/*
	// int			ret;
	// ret = ft_termcap(data);
	// printf("ret = %d\n", ret);
*/