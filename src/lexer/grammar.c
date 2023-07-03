/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:20:09 by Bea               #+#    #+#             */
/*   Updated: 2023/07/02 20:31:06 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	apply_grammar(t_bigshell *data)
// {
// 	t_token	*tok;

// 	tok = data->token;
// 	while (tok != NULL)
// 	{
// 		if (tok->type == PIPE)
// 			apply_pipe(data, tok);
// 		else if (tok->type == REDIR)
// 			apply_redir(data, tok);
// 		else if (tok->type == CMD)
// 			apply_cmd(data, tok);
// 		tok = tok->next;
// 	}
// }
