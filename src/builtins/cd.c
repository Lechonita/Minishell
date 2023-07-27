/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:18 by Bea               #+#    #+#             */
/*   Updated: 2023/07/27 16:40:31 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonctions autorisées : chdir, getcwd, opendir, readdir, closedir*/

static int	set_env_value(t_bigshell *data, char *name, char *value)
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

static char	*get_env_value(t_bigshell *data, char *name)
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

static int	update_pwd(t_bigshell *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Minishell: cd");
		return (EXIT_FAILURE);
	}
	if (get_env_value(data, "PWD"))
	{
		if (set_env_value(data, "OLDPWD", get_env_value(data, "PWD")) == 1)
			return (EXIT_FAILURE);
	}
	else
	{
		do_export_cd(data, "PWD", cwd);
		do_export_cd(data, "OLDPWD", NULL);
	}
	// {
	// 	env_addback(&data->env, env_new_cd(data, "PWD", cwd));
	// 	env_addback(&data->env, env_new_cd(data, "OLDPWD", NULL));
	// }
	if (set_env_value(data, "PWD", cwd) == 1)
	{
		free(cwd);
		return (EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

static char	*get_dir(t_bigshell *data, char **args)
{
	char	*dir;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		dir = get_env_value(data, "HOME");
		if (!dir)
			ft_putstr_fd(HOME_NOT_SET, 2);
	}
	else if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		if (args[2])
		{
			ft_putstr_fd(W_CD_ARG, 2);
			return (NULL);
		}
		dir = get_env_value(data, "OLDPWD");
		if (!dir)
			ft_putstr_fd(OLDPWD_NOT_SET, 2);
	}
	else
		dir = args[1];
	return (dir);
}

int	change_directory(char **args, t_bigshell *data)
{
	char	*dir;

	dir = get_dir(data, args);
	if (!dir || !data)
		return (EXIT_FAILURE);
	if (chdir(dir) == -1)
	{
		error_cd(dir);
		return (EXIT_FAILURE);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_putstr_fd(ft_strjoin(dir, "\n"), STDOUT_FILENO);
	if (update_pwd(data) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
