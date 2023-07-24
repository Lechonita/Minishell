/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:40 by Bea               #+#    #+#             */
/*   Updated: 2023/07/24 19:01:19 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_env(t_bigshell *data)
{
	t_env	*el;

	el = data->env;
	while (el)
	{
		if (el->to_export == FALSE)
			printf("%s=%s\n", el->name, el->value);
		if (el->to_export == TRUE)
			printf("%s\n", el->name);
		el = el->next;
	}
	return (EXIT_SUCCESS);
}
