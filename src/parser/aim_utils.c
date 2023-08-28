/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:20:03 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/28 17:37:01 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	last_is_dollar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '$')
		return (1);
	return (0);
}

char	*def_tok_value(char *value, char *next_value)
{
	if (!value || !next_value)
		return (NULL);
	if (last_is_dollar(value) == 1)
		return (freejoin(value, next_value));
	return (join_spac(value, next_value, " "));
}
