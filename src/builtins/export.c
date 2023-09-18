/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:51 by Bea               #+#    #+#             */
/*   Updated: 2023/09/18 15:09:39 by jrouillo         ###   ########.fr       */
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

static void	alphabetical_sort_env(t_bigshell *data)
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

static char	*join_to_export(char *name, char *value)
{
	char	*tmp;

	tmp = ft_strjoin("declare -x ", name);
	if (value != NULL)
	{
		tmp = free_strjoin(tmp, "=\"");
		tmp = free_strjoin(tmp, value);
		tmp = free_strjoin(tmp, "\"");
	}
	return (tmp);
}

// "\'\"\\$ ,.:/[{]}+=-?&*^%#@!~"

static void	add_variables_in_env(t_bigshell *data, char **args)
{
	t_env	*var;
	char	*name;
	char	*value;
	size_t	i;

	i = 0;
	while (args[i] != NULL)
	{
		name = find_name(args[i]);
		if (name_exists(data->env, name) == TRUE)
			unset_var(name, &args[i], data);
		value = find_value(args[i]);
		var = init_var(data, name, value);
		env_addback(&data->env, var);
		free(value);
		free(name);
		++i;
	}
}

int	export_var(char **args, t_bigshell *data, int fd_out)
{
	t_env	*el;
	char	*var;

	el = data->env;
	if (args[1] == NULL)
	{
		alphabetical_sort_env(data);
		while (el)
		{
			if (ft_strncmp(el->name, "_", 2) != 0
				&& (el->to_export == FALSE || el->to_export == 2))
			{
				var = join_to_export(el->name, el->value);
				ft_putendl_fd(var, fd_out);
				free(var);
			}
			el = el->next;
		}
	}
	else
		add_variables_in_env(data, args + 1);
	return (EXIT_SUCCESS);
}
