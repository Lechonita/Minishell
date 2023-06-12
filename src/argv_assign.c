/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:12:54 by lechon            #+#    #+#             */
/*   Updated: 2023/06/09 14:42:02 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int    ft_quotes(t_argv *new, char *line, char limiter, int i)
// {
// 	char    *value;
// 	int     n;

// 	if (limiter == 39)
// 		new->type = TYPE_SINGLE_QUOTES;
// 	if (limiter == 34)
// 		new->type = TYPE_DOUBLE_QUOTES;
// 	value = malloc(sizeof(char) * ft_strlen(line));
// 	if (!value)
// 		return ;
// 	n = 0;
// 	printf("Ici ma line = -%s-\n", line);
// 	while (line[n] && line[n] != limiter)
// 	{
// 		value[n] = line[n];
// 		n++;
// 		i++;
// 	}
// 	if (line[n] != '\0')
// 		value[n] = limiter;
// 	new->value = value;
// 	return (i);
// }

// void	display_argv_struct(t_bigshell *data)
// {
// 	while (data->argv)
// 	{
// 		printf("INDEX = %d\n", data->argv->index);
// 		printf("TYPE  = %d\n", data->argv->type);
// 		printf("VALUE = %s\n", data->argv->value);
// 		data->argv = data->argv->next;
// 	}
// }