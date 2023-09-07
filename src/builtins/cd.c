/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:18 by Bea               #+#    #+#             */
/*   Updated: 2023/09/07 12:30:33 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonctions autorisées : chdir, getcwd, opendir, readdir, closedir*/

static int	error_cd(char *str)
{
	char	*res;

	res = malloc(sizeof(char) * (43 + ft_strlen(str)));
	if (!res)
		return (EXIT_FAILURE);
	res = ft_strjoin("Minishell: cd: ", str);
	res = free_strjoin(res, ": No such file or directory\n");
	ft_putstr_fd(res, 2);
	free(res);
	g_global.exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

static char	*get_dir(t_bigshell *data, char **args)
{
	char	*dir;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		dir = get_env_value(data, "HOME");
		if (!dir)
			ft_error(EXIT_FAILURE, HOME_NOT_SET);
	}
	else if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		if (args[2])
			return (ft_error(EXIT_FAILURE, W_CD_ARG), NULL);
		dir = get_env_value(data, "OLDPWD");
		if (!dir)
			ft_error(EXIT_FAILURE, OLDPWD_NOT_SET);
	}
	else
		dir = args[1];
	return (dir);
}

int	change_directory(char **args, t_bigshell *data)
{
	char	*dir;
	char	*tmp;

	dir = get_dir(data, args);
	if (!dir || !data)
		return (EXIT_FAILURE);
	if (chdir(dir) == -1)
		return (error_cd(dir), EXIT_FAILURE);
	tmp = ft_strjoin(dir, "\n");
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_putstr_fd(tmp, STDOUT_FILENO);
	free(tmp);
	if (update_pwd(data) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
