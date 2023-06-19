/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/19 15:55:23 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_new_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
		i++;
	line[i - 1] = '\0';
	return (line);
}

void	ft_read_line(t_bigshell *data)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	// printf("line\n");
	while (1)
	{
		write(1, "bigshell42> ", 12);
		line = get_next_line(0);
		// printf("line = %s\n", line);
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) - 1 == 4)
			break ;
		if (line)
		{
			// data->history[i] = remove_new_line(line);
			// init_argv(data, data->history[i - 1]);
			init_argv(data, line);
			// display_argv_struct(data); // A retirer
			i++;
		}
		if (i == 50)
			i = 0;
		free(line);
	}
	free(line);
}


/* delimiteurs =
> 
<
& (bonus)
|
( (bonus)
) (bonus)
\0 */