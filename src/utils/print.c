/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/29 14:35:59 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	t_line	*el;

	el = data->line;
	while (el != NULL)
	{
		printf("[idx] %2d ", el->index);
		printf("[type] %2d ", el->type);
		printf("[dq] %2d ", el->dq);
		printf("[sq] %2d ", el->sq);
		printf("[c] %c\n", el->c);
		el = el->next;
	}
}

void	print_t_token(t_bigshell *data)
{
	t_token	*el;

	el = data->token;
	while (el)
	{
		printf("[%2d] ", el->index);
		printf("pos in line %2d ", el->pos);
		printf("type %d", el->type);
		printf(" : %s\n", el->value);
		el = el->next;
	}
}
/* fonction qui permet d'afficher t_env
	(equivalent de la commande "env" ou "printenv" dans le terminal) */

void	display_env_struct(t_bigshell *data)
{
	t_env	*el;

	if (!data->env)
		ft_exit(EXIT_FAILURE, "No env to display\n");
	el = data->env;
	while (el != NULL)
	{
		printf("[%2d] %s=%s\n", el->index, el->name, el->value);
		el = el->next;
	}
}
