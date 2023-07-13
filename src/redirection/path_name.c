/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:03:19 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/13 17:35:36 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"

char	*in_file_path(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	if (count_file(data, LESS) == 1)
	{
		while (tok->next != NULL)
		{
			if (tok->type == LESS && tok->next->type == WORD)
				return (tok->next->value);
			tok = tok->next;
		}		
	}
	// else
	// 	check_access_file(data);
	return (NULL);
}

char	*out_file_path(t_bigshell *data)
{
	t_token	*tok;

	tok = data->token;
	if (count_file(data, GREAT) == 1)
	{
		while (tok->next != NULL)
		{
			if (tok->type == GREAT && tok->next->type == WORD)
				return (tok->next->value);
			tok = tok->next;
		}
	}
	// else
	// 	check_access_file(data);
	return (NULL);
}