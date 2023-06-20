/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 14:29:06 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(int err_no, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(err_no);
}

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("[%2d] %s\n", i, strs[i]);
		i++;
	}
}

void	print_t_line(t_bigshell *data)
{
	while (data->line)
	{
		printf("=================================\n");
		printf("[index] %d\n", data->line->index);
		printf("[type] %d\n", data->line->type);
		printf("[dq] %d\n", data->line->dq);
		printf("[sq] %d\n", data->line->sq);
		printf("[c] %c\n", data->line->c);
		data->line = data->line->next;
	}
}
