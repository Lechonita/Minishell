/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:51 by Bea               #+#    #+#             */
/*   Updated: 2023/09/14 15:50:33 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	swap_env(t_env *el, t_env *tmp)
{
	char	*tmp_name;
	char	*tmp_value;
	int		tmp_to_export;

	tmp_name = el->name;
	tmp_value = el->value;
	tmp_to_export = el->to_export;
	el->name = tmp->name;
	el->value = tmp->value;
	el->to_export = tmp->to_export;
	tmp->name = tmp_name;
	tmp->value = tmp_value;
	tmp->to_export = tmp_to_export;
	return ;
}

void	alphabetical_sort_env(t_bigshell *data)
{
	t_env	*el;
	t_env	*tmp;

	el = data->env;
	while (el)
	{
		tmp = el->next;
		while (tmp)
		{
			if (ft_strcmp(el->name, tmp->name) > 0)
				swap_env(el, tmp);
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
		if (ft_strncmp(el->name, "_", 2) != 0
			&& (el->to_export == FALSE || el->to_export == 2))
		{
			if (!el->value)
				printf("declare -x %s\n", el->name);
			else
				printf("declare -x %s=\"%s\"\n", el->name, el->value);
		}
		el = el->next;
	}
	return ;
}

// "\'\"\\$ ,.:/[{]}+=-?&*^%#@!~"

int	export_var(char **args, t_bigshell *data)
{
	if (args[1] == NULL)
		print_declare_env(data);
	return (EXIT_SUCCESS);
}
