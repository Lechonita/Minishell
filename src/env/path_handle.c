/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:34:26 by lechon            #+#    #+#             */
/*   Updated: 2023/06/27 10:16:42 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*ft_strjoin_bis(char *s1, char *s2)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, s2);
	if (!str)
		return (NULL);
	free(tmp);
	return (str);
}

/* Fonction qui cherche le chemin absolu d'une commande dans le PATH */
char	*find_path_to_cmd(t_bigshell *data, char *cmd)
{
	t_env	*el;
	char	*command;
	int		i;

	i = -1;
	el = data->env;
	while (el)
	{
		if (ft_strncmp(el->name, "PATH", 4) == 0)
		{
			if (el->env_split == NULL && ft_strchr(cmd, '/') == NULL)
				error_not_found(data, FILE_NOT_FOUND, cmd);
			if (ft_strchr(cmd, '/') != NULL)
				command = handle_good_path(data, cmd);
			while (el->env_split[++i])
			{
				command = ft_strjoin_bis(el->env_split[i], cmd);
				if (access(command, F_OK & X_OK) == 0)
					return (command);
				free(command);
			}
		}
		el = el->next;
	}
	return (NULL);
}

/* fonction qui sépare les différents chemin de la variable $PATH */
void	get_path(t_bigshell *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		tmp->env_split = ft_split(tmp->value, ':');
		if (!tmp->env_split)
			return (ft_free_all(data), ft_exit(EXIT_FAILURE, W_SPLIT_ENV));
		tmp = tmp->next;
	}
	return ;
}

/*
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
		{
			tmp->env_paths = ft_split(tmp->value, ':');
			if (!tmp->env_paths)
				return (ft_free_all(data), ft_exit(EXIT_FAILURE, W_SPLIT_ENV));
		}
		tmp = tmp->next;
	}
*/