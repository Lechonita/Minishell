/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/13 17:26:48 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_history(t_bigshell *data, char *line, int i)
{
	size_t	len;

	len = ft_strlen(line);
	data->history[i] = ft_strndup(line, len - 1);
	if (!data->history[i])
		return ;
}

void	ft_read_line(t_bigshell *data)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	data->history = ft_calloc(50, sizeof(char *));
	while (1)
	{
		write(1, "bigshell@42> ", 12);
		line = get_next_line(0);
		if (!ft_strncmp(line, "exit", 4) && ft_strlen(line) - 1 == 4)
			break ;
		if (line)
		{
			ft_save_history(data, line, i);
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