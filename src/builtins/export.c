/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:51 by Bea               #+#    #+#             */
/*   Updated: 2023/09/06 15:59:18 by bebigel          ###   ########.fr       */
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
		if (ft_strncmp(el->name, "_", 2) != 0 && el->to_export == FALSE)
			printf("declare -x %s=\"%s\"\n", el->name, el->value);
		el = el->next;
	}
	return ;
}

// "\'\"\\$ ,.:/[{]}+=-?&*^%#@!~"

void	do_export(t_bigshell *data, char **args)
{
	int		i;
	t_env	*el;

	i = 1;
	while (args[i])
	{
		el = data->env;
		while (el)
		{
			if (ft_strncmp(el->name, args[i], ft_strlen(el->name)) == 0)
				el->to_export = FALSE;
			el = el->next;
		}
		i++;
	}
	return ;
}

int	export_var(char **args, t_bigshell *data)
{
	if (args[1] == NULL)
		print_declare_env(data);
	else
		do_export(data, args);
	return (EXIT_SUCCESS);
}

/*


void	do_export(t_bigshell *data, char **args)
{
	int		i;
	int		len;
	t_env	*env;

	i = 1;
	len = 0;
	env = data->env;
	while (env->next)
	{
		len++;
		env = env->next;
	}
	dprintf(2, "len = %d\n", len);
	while (args[i])
	{
		dprintf(2, "args[%d] → %s\n", i, args[i]);
		env_addback(&data->env, env_new(args[i], len - 1, TRUE));
		i++;
	}
	return ;
}
*/