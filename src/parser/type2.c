/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:52:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/06/30 15:59:08 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

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
