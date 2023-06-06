/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/06 17:28:49 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_bigshell		*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	// init_argv(ac, av);
	init_env(data, env);
	if (ac == 2)
		ft_printf("%s\n", av[1]);
	return (0);
}
