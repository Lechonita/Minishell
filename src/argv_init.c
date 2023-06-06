/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechon <lechon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:39:00 by lechon            #+#    #+#             */
/*   Updated: 2023/06/06 16:39:40 by lechon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui rempli la donnee bigshell->argv.
	Les cas de figures a prendre en compte :
	- s'il y a des guillemets au milieu des commandes (ex: l"s")
		= doit fonctionner normalement
	- s'il y a des guillements pour une string (ex: "hello world")
		= doit representer une seule commande
	Prochaines etapes : verifier ensuite si les commandes
		sont correctes (access) et puis les executer */

// void	init_argv(t_bigshell *data, int ac, char *av[])
// {

// }