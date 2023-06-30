/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:45:14 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/30 15:57:34 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expander.h"

/* Toutes ces fonctions permettent de determiner la position de :
	- l'ouverture des doubles guillemets
	- la fermeture des doubles guillemets
	- l'ouverture des simples guillemets
	- la fermeture des simples guillemets*/

// int	find_end_dq(t_line *line)
// {
// 	if (!line)
// 		return (-1);
// 	while (line)
// 	{
// 		if (line->dq == 2)
// 			return (line->index);
// 		line = line->next;
// 	}
// 	return (-1);
// }

// int	find_start_dq(t_line *line)
// {
// 	if (!line)
// 		return (-1);
// 	while (line)
// 	{
// 		if (line->dq == 1)
// 			return (line->index);
// 		line = line->next;
// 	}
// 	return (-1);
// }

// int	find_end_sq(t_line *line)
// {
// 	if (!line)
// 		return (-1);
// 	while (line)
// 	{
// 		if (line->sq == 2)
// 			return (line->index);
// 		line = line->next;
// 	}
// 	return (-1);
// }

// int	find_start_sq(t_line *line)
// {
// 	if (!line)
// 		return (-1);
// 	while (line)
// 	{
// 		if (line->sq == 1)
// 			return (line->index);
// 		line = line->next;
// 	}
// 	return (-1);
// }
