/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:49:49 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/07 14:28:47 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_env_value(t_bigshell *data, char *name, char *value)
{
	t_env	*env;

	if (!data || !name)
		return (EXIT_FAILURE);
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (value && ft_strcmp(env->value, value) == 0)
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

void	export_pwd_after_unset(t_bigshell *data, char *new_pwd)
{
	int		len;
	char	*new_env;
	t_env	*env;

	len = 0;
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(" ");
		}
		len++;
		env = env->next;
	}
	new_env = ft_strjoin("PWD=", new_pwd);
	env_addback(&data->env, env_new(new_env, len, TRUE));
	free(new_env);
	return ;
}

int	update_pwd(t_bigshell *data)
{
	char	*new_pwd;
	char	*new_oldpwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		ft_error(errno, strerror(errno));
	new_oldpwd = get_env_value(data, "PWD");
	if (new_oldpwd && set_env_value(data, "OLDPWD", new_oldpwd) == 1)
		return (free(new_pwd), EXIT_FAILURE);
	if (new_oldpwd == NULL)
		return (export_pwd_after_unset(data, new_pwd), free(new_pwd), 0);
	if (set_env_value(data, "PWD", new_pwd) == 1)
		return (free(new_pwd), EXIT_FAILURE);
	return (free(new_pwd), EXIT_SUCCESS);
}
