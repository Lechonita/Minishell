/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:52:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/20 16:10:58 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_dollar(char c)
{
	if (c == '$')
		return (TYPE_DOLLAR);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (TYPE_BLANK);
	return (0);
}

int	ft_is_single_quote(char c)
{
	if (c == '\'')
		return (TYPE_SINGLE_QUOTES);
	return (0);
}

int	ft_is_double_quote(char c)
{
	if (c == '\"')
		return (TYPE_DOUBLE_QUOTES);
	return (0);
}
