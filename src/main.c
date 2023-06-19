/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 11:10:18 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_bigshell	*data;
	char		*buf;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	init_env(data, env);
	while (1)
	{
		buf = readline(">> ");
		if (buf[0] != '\0')
			add_history(buf);
		if (!ft_strncmp(buf, "exit", 4) && ft_strlen(buf) == 4)
			break ;
		printf("[%s]\n", buf);
		free(buf);
	}
	free(buf);
	// ft_read_line(data);
	// init_history(data);
	if (ac == 2)
		ft_printf("%s\n", av[1]);
	ft_free_all(data);
	return (0);
}
