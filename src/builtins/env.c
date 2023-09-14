/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:40 by Bea               #+#    #+#             */
/*   Updated: 2023/09/14 13:55:27 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_env(t_bigshell *data, char *cmd, char **args)
{
	t_env	*el;

	(void)cmd;
	if (args[1] != NULL)
		return (ft_error(1, W_BUILT_ENV), EXIT_FAILURE);
	el = data->env;
	while (el)
	{
		if (el->to_export == FALSE)
			printf("%s=%s\n", el->name, el->value);
		el = el->next;
	}
	return (EXIT_SUCCESS);
}
