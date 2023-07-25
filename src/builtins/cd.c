/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:18 by Bea               #+#    #+#             */
/*   Updated: 2023/07/25 18:42:09 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Fonctions autorisées : chdir, getcwd, opendir, readdir, closedir*/

int	change_directory(char **args, t_bigshell *data)
{
	(void)data;
	(void)args;
	return (EXIT_SUCCESS);
}
