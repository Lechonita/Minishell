/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:49:49 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/06 22:19:48 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	find_next_index(t_bigshell *data)
// {
// 	t_env	*env;
// 	int		i;

// 	if (!data)
// 		return (-1);
// 	env = data->env;
// 	i = 0;
// 	while (env)
// 	{
// 		i++;
// 		env = env->next;
// 	}
// 	return (i);
// }

// t_env	*env_new_cd(t_bigshell *data, char *name, char *value)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return (NULL);
// 	new->name = name;
// 	new->value = value;
// 	new->index = find_next_index(data);
// 	new->to_export = FALSE;
// 	new->next = NULL;
// 	return (new);
// }

void	do_export_cd(t_bigshell *data, char *name, char *value)
{
	t_env	*env;

	if (!data || !name)
		return ;
	env = data->env;
	dprintf(2, "\033[3;37mname = %s\033[0m\n", name);
	dprintf(2, "\033[3;37mvalue = %s\033[0m\n", value);
	while (env)
	{
		dprintf(2, "\033[3;37mname = %s cmp %d\033[0m\n", name, ft_strcmp(env->name, name));
		if (ft_strcmp(env->name, name) == 0 && value)
			env->value = ft_strdup(value);
		else if (ft_strcmp(env->name, name) == 0 && !value)
			env->value = NULL;
		env = env->next;
	}
}

int	set_env_value(t_bigshell *data, char *name, char *value)
{
	t_env	*env;

	if (!data || !name || !value)
		return (EXIT_FAILURE);
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (ft_strcmp(env->value, value) == 0)
				return (EXIT_SUCCESS);
			free(env->value);
			env->value = ft_strdup(value);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	return (EXIT_FAILURE);
}

char	*get_env_value(t_bigshell *data, char *name)
{
	t_env	*env;

	if (!data || !name)
		return (NULL);
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	update_pwd(t_bigshell *data)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	dprintf(2, "\033[3;33mcurrent wd = %s\033[0m\n", cwd);
	if (!cwd)
		ft_error(errno, strerror(errno));
	tmp = get_env_value(data, "PWD");
	dprintf(2, "\033[3;36mancien tmp = %s\033[0m\n", tmp);
	if (tmp)
	{
		if (set_env_value(data, "OLDPWD", tmp) == 1)
			return (EXIT_FAILURE);
	}
	else
	{
		do_export_cd(data, "PWD", cwd);
		do_export_cd(data, "OLDPWD", tmp);
	}
	if (set_env_value(data, "PWD", cwd) == 1)
		return (free(cwd), EXIT_FAILURE);
	return (free(cwd), EXIT_SUCCESS);
}



// int	get_export_value(t_bigshell *data, char *name)
// {
// 	t_env	*env;

// 	if (!data || !name)
// 		return (TRUE);
// 	env = data->env;
// 	while (env)
// 	{
// 		if (ft_strcmp(env->name, name) == 0 && env->to_export == FALSE)
// 			return (FALSE);
// 		env = env->next;
// 	}
// 	return (TRUE);
// }
