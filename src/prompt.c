/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/07 18:05:35 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_line(t_bigshell *data, int i)
{
	char    *line;

	while (1)
	{
		write(1, "bigshell42> ", 12);
		line = get_next_line(0);
		if (line)
		{
			data->history[i] = line;
			argv_init(data);
		}
		free(line);
	}
}

void    ft_prompt(t_bigshell *data)
{
	int		i;

	i = -1;
	while (++i <= 50)
	{
		get_line(data, i);
		if (i == 50)
			i = -1;
	}
}


/* delimiteurs =
> 
<
& (bonus)
|
( (bonus)
) (bonus)
\0 */