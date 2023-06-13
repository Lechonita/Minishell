/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/13 15:36:37 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_history(t_bigshell *data, char *line, int i)
{
	printf("Ici, mon i = %d\n", i);
	data->history[i] = ft_strndup(line, ft_strlen(line));
	data->history[i] = remove_new_line(data->history[i]);
	printf("Dans la fonction save_data->history[i], data->history[i] = %s\n", data->history[i]);
}

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
	while (1)
	{
		printf("Je rentre dans la boucle read_line\n");
		write(1, "bigshell@42> ", 12);
		line = get_next_line(0);
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) - 1 == 4)
			break ;
		if (line)
		{
			ft_save_history(data, line, i);
			printf("Dans READ LINE, mon data->history = %s\n", data->history[i]);
			// init_argv(data, data->history[i]);
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