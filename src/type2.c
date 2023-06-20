/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:52:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/20 13:54:40 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (7);
	return (0);
}

int	ft_is_single_quote(char c)
{
	if (c == '\'')
		return (6);
	return (0);
}

int	ft_is_double_quote(char c)
{
	if (c == '\"')
		return (5);
	return (0);
}
