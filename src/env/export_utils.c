/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:58 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/18 15:28:22 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


char	*find_value(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i] && str[i] != '=')
		i++;
	i += (str[i] != 0);
	while (str[i])
		res[j++] = str[i++];
	return (res);
}

int	name_exists(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

char	*find_name(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		res[j++] = str[i++];
	}
	return (res);
}

static int	find_next_index(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		++i;
	}
	return (i);
}

t_env	*init_var(t_bigshell *data, char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(name);
	new->to_export = FALSE;
	new->value = ft_strdup(value);
	new->index = find_next_index(data->env);
	new->next = NULL;
	return (new);
}
