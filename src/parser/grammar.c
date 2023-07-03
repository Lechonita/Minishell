/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:20:09 by Bea               #+#    #+#             */
/*   Updated: 2023/07/03 11:40:25 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

// void	apply_grammar(t_bigshell *data)
// {
// 	t_token	*tok;

// 	tok = data->token;
// 	while (tok != NULL)
// 	{
// 		if (tok->aim == PIPE)
// 			apply_pipe(data, tok);
// 		else if (tok->aim == REDIR)
// 			apply_redir(data, tok);
// 		else if (tok->aim == SIMPLE_CMD)
// 			apply_cmd(data, tok);
// 		else if (tok->aim == BUILTIN)
// 			apply_builtin(data, tok);
// 		tok = tok->next;
// 	}
// }
