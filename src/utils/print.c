/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/04 16:10:29 by Bea              ###   ########.fr       */
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

void	print_cmd_lst(t_bigshell *data)
{
	t_cmd	*el;
	int		j;

	el = data->exec->cmd;
	while (el != NULL)
	{
		dprintf(2, "path : %s, command n°%d → %s\n", el->cmd,
			el->idx_cmd, el->cmd_arg[0]);
		j = 0;
		while (el->cmd_arg[j])
		{
			dprintf(2, "\t\t\t cmd_arg [%d] → %s\n", j, el->cmd_arg[j]);
			j++;
		}
		el = el->next;
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
		// printf("tok %2d ", el->type);
		printf(": %12s ", el->value);
		printf("→ %2d\n", el->aim);
		el = el->next;
	}
	printf("_______________________________________________\n");
}
/* fonction qui permet d'afficher t_env
	(equivalent de la commande "env" ou "printenv" dans le terminal) */
void	display_env_struct(t_bigshell *data)
{
	t_env	*el;

	// if (!data->env)
	// 	ft_exit(EXIT_FAILURE, "No env to display\n");
	el = data->env;
	while (el != NULL)
	{
		printf("[%2d] %s=%s\n", el->index, el->name, el->value);
		el = el->next;
	}
}
