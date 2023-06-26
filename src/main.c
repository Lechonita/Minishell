/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/26 09:19:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_bigshell	*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	set_signal();
	ft_readline(data);
	init_env(data, env);
	// print_strs(data->history);
	// display_env_struct(data);
	if (ac == 2)
		printf("%s\n", av[1]);
	ft_free_all(data);
	return (0);
}

/*
terminal capabilities :
	int			ret;
	ret = ft_termcap(data);
	printf("ret = %d\n", ret);
*/