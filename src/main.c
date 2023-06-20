/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:28:05 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 14:06:46 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_readline(t_bigshell *data)
{
	char	*buf;

	while (1)
	{
		buf = readline(">> ");
		if (!ft_strncmp(buf, "exit", 4) && ft_strlen(buf) == 4)
			break ;
		if (buf[0] != '\0')
		{
			// add_history(data, buf);
			init_line(data, buf);
		}
		printf("[%s]\n", buf);
		free(buf);
	}
	free(buf);
}

/* BEA 
	J'ai sorti la partie readline du main parce qu'il depassait deja 25 lignes.
	J'ai tout mis dans la fonction ft_readline juste au dessus !
	Du coup plus besoin des fonctions qui sont dans le fichier prompt.c */

int	main(int ac, char *av[], char **env)
{
	t_bigshell	*data;

	data = ft_calloc(1, sizeof(t_bigshell));
	if (!data)
		return (0);
	init_env(data, env);	// recuperer les lignes de env dans t_env
	ft_readline(data);		// prompt + interpretation de la ligne (buf)
	if (ac == 2)
		printf("%s\n", av[1]);
	ft_free_all(data);
	return (0);
}
