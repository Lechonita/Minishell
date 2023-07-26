/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:18 by Bea               #+#    #+#             */
/*   Updated: 2023/07/26 15:41:57 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonctions autorisées : chdir, getcwd, opendir, readdir, closedir*/

// static char	*get_env_path(t_env *env, char *str, size_t len)
// {
	
// }

// static int	exists_in_env(char **env_paths, char *oldpwd)
// {
// 	int		i;

// 	if (!*env_paths || !env_paths || !oldpwd)
// 		return (0);
// 	i = -1;
// 	while (env_paths[++i])
// 	{
// 		if (ft_strcmp(env_paths[i], oldpwd) == 0)
			
// 	}
// }

// static int	update_oldpwd(t_bigshell *data)
// {
// 	char	cwd[_PC_PATH_MAX];
// 	char	*oldpwd;
// 	int		ret;

// 	ret = getcwd(cwd, _PC_PATH_MAX);
// 	if (!ret)
// 		return (EXIT_FAILURE);
// 	oldpwd = ft_strjoin("OLDPWD=", cwd);
// 	if (!oldpwd)
// 		return (EXIT_FAILURE);
// 	if (exists_in_env(data->env_paths, oldpwd) == 1)
// 		add_in_env(oldpwd, data->env);
// }

// static int	go_back_home(t_bigshell *data)
// {
// 	int		ret;
// 	char	*env_path;

// 	ret = update_oldpwd(data);
// 	env_path = get_env_path(data->env, "HOME", 4);
// 	if (!env_path)
// 	{
// 		ft_putstr_fd(HOME_NOT_FOUND, 2);
// 		ret = EXIT_FAILURE;
// 	}
// 	return (ret);
// }

// int	change_directory(char **args, t_bigshell *data)
// {
// 	int		ret;

// 	if (!data)
// 		return (EXIT_FAILURE);
// 	ret = EXIT_SUCCESS;
// 	if (!args[1] || ft_strcmp(args[1], "~") == 0)
// 		ret = go_back_home(data);
// 	else if (ft_strcmp(args[1], "-") == 0)
// 		// afficher la ou on va et retourner un directroy en arriere
// 	else
// 	{
		
// 	}
// 	return (ret);
// }

static int	update_pwd(t_bigshell *data)
{
	char	cwd[_PC_PATH_MAX];

	if (get_env_value(data, "PWD"))
	{
		if ()
	}
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
	if (!dir)
		return (EXIT_FAILURE);
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_putstr_fd(dir, STDOUT_FILENO);
	if (update_pwd(data) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
