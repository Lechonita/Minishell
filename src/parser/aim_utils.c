/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:20:03 by jrouillo          #+#    #+#             */
/*   Updated: 2023/08/30 12:05:06 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

char	*join_space(char *s1, char *s2, char *to_add)
{
	char	*tmp;
	char	*str;

	tmp = freejoin(s1, to_add);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

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
