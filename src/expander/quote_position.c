/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:45:14 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/21 14:20:42 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_end_dq(t_line *line)
{
	if (!line)
		return (-1);
	while (line)
	{
		if (line->dq == 2)
			return (line->index);
		line = line->next;
	}
	return (-1);
}

int	find_start_dq(t_line *line)
{
	if (!line)
		return (-1);
	while (line)
	{
		if (line->dq == 1)
			return (line->index);
		line = line->next;
	}
	return (-1);
}

int	find_end_sq(t_line *line)
{
	if (!line)
		return (-1);
	while (line)
	{
		if (line->sq == 2)
			return (line->index);
		line = line->next;
	}
	return (-1);
}

int	find_start_sq(t_line *line)
{
	if (!line)
		return (-1);
	while (line)
	{
		if (line->sq == 1)
			return (line->index);
		line = line->next;
	}
	return (-1);
}
