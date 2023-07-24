/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:51 by Bea               #+#    #+#             */
/*   Updated: 2023/07/20 15:41:48 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	alphabetical_sort_env(t_bigshell *data)
{
	t_env	*el;
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;

	el = data->env;
	while (el)
	{
		tmp = el->next;
		while (tmp)
		{
			if (ft_strcmp(el->name, tmp->name) > 0)
			{
				tmp_name = el->name;
				tmp_value = el->value;
				el->name = tmp->name;
				el->value = tmp->value;
				tmp->name = tmp_name;
				tmp->value = tmp_value;
			}
			tmp = tmp->next;
		}
		el = el->next;
	}
	return ;
}

void	print_declare_env(t_bigshell *data)
{
	t_env	*el;

	el = data->env;
	alphabetical_sort_env(data);
	while (el)
	{
		if (ft_strncmp(el->name, "_", 2) != 0)
			printf("declare -x %s=\"%s\"\n", el->name, el->value);
		el = el->next;
	}
	return ;
}

int	export_var(char *cmd, char **args, t_bigshell *data)
{
	dprintf(2, "%s\n", cmd);
	if (args[1] == NULL)
		print_declare_env(data);
	return (EXIT_SUCCESS);
}
