/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/18 12:38:05 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		dprintf(2, "[%2d] %s\n", i, strs[i]);
		i++;
	}
}

/* fonction qui permet d'afficher t_env
	(equivalent de la commande "env" ou "printenv" dans le terminal) */
void	display_env_struct(t_bigshell *data)
{
	t_env	*el;

	el = data->env;
	while (el != NULL)
	{
		printf("[%2d] %s=%s\n", el->index, el->name, el->value);
		el = el->next;
	}
}
