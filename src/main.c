/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/06 20:11:33 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_bigshell		*data;
	int				i;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	// init_argv(data, ac, av);
	init_env(data, env);
	i = -1;
	while (++i <= 50)
	{
		get_line(data, i);
		if (i == 50)
			i = -1;
	}
	if (ac == 2)
		ft_printf("%s\n", av[1]);
	return (0);
}
