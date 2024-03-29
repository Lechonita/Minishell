/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:34:26 by lechon            #+#    #+#             */
/*   Updated: 2023/09/13 16:46:59 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

static char	*ft_strjoin_bis(char *s1, char *s2, char *to_add)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, to_add);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

/* fonction qui vérifie l'acces des commandes avec le chemin absolu */
static char	*handle_good_path(t_bigshell *data, char *command)
{
	if (access(command, F_OK & X_OK) == 0)
		return (command);
	else if (access(command, F_OK) < 0)
		error_not_found(data, FILE_NOT_FOUND, command);
	else if (access(command, X_OK) < 0)
		error_not_found(data, CMD_NOT_FOUND, command);
	return (NULL);
}

/* Fonction qui cherche le chemin absolu d'une commande dans le PATH */
char	*find_path_to_cmd(t_bigshell *data, char *cmd, char *path)
{
	char	*command;
	int		i;

	i = -1;
	if (data->env_paths == NULL && ft_strchr(cmd, '/') == NULL)
		error_not_found(data, FILE_NOT_FOUND, cmd);
	if (ft_strchr(cmd, '/') != NULL)
	{
		command = handle_good_path(data, cmd);
		free(path);
		return (ft_strdup(command));
	}
	while (data->env_paths[++i])
	{
		command = ft_strjoin_bis(data->env_paths[i], cmd, "/");
		if (access(command, F_OK & X_OK) == 0)
			return (command);
		free(command);
	}
	free(path);
	return (NULL);
}

/* fonction qui sépare les différents chemin de la variable $PATH */
int	get_path(t_bigshell *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
		{
			data->env_paths = ft_split(tmp->value, ':');
			if (!data->env_paths)
				return (ft_error(EXIT_FAILURE, W_SPLIT_ENV), FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
