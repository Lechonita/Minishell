/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:34:19 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/22 18:07:28 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	interpret_open_quotes(t_line *line, char quote)
{
	char	*rest;

	if (!line || !quote)
		return ;
	rest = NULL;
	while (line)
	{
		line->type = TYPE_WORD;
		line = line->next;
	}
	
}
