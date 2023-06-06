/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/06 21:28:31 by lechon           ###   ########.fr       */
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



/* delimiteurs =
> 
<
& (bonus)
|
( (bonus)
) (bonus)
\0 */