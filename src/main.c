/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/12 17:07:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_bigshell		*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	init_env(data, env);
	ft_read_line(data);
	if (ac == 2)
		ft_printf("%s\n", av[1]);
	ft_free_all(data);
	return (0);
}
