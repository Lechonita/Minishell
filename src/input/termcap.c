/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:48:56 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/30 15:58:25 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/input.h"

int	init_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
		return (fprintf(stderr, "TERM must be set (see 'env').\n"), -1);
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		return (fprintf(stderr, "No access to the termcap database\n"), -1);
	else if (ret == 0)
		return (fprintf(stderr, "type %s not defined in database\n", term_type),
			-1);
	return (0);
}

int	ft_termcap(t_bigshell *data)
{
	int		ret;
	int		col_count;
	int		line_count;
	char	*str_cap;
	char	*cm_cap;

	(void)data;
	ret = init_term();
	if (ret == 0)
	{
		col_count = tgetnum("co");
		line_count = tgetnum("li");
		if (col_count == -1 || line_count == -1)
			return (fprintf(stderr, "Error while getting terminal size\n"), -1);
		if (tgetflag("am") == 0)
			return (fprintf(stderr, "Automatic margins : not supported\n"), -1);
		str_cap = tgetstr("us", NULL);
		printf("us = souligne le texte %s\n", str_cap);
		tputs(str_cap, 1, putchar);
		cm_cap = tgetstr("cm", NULL);
		tputs(tgoto(cm_cap, 5, 5), 1, putchar);
	}
	return (ret);
}
