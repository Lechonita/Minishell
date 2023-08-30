/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/08/30 16:57:04 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_t_line(t_line *line)
{
	t_line		*el;
	const char	*tokentype_str[] = {
		"WORD",
		"DQUOTE",
		"SQUOTE",
		"\n",
		"BLANK",
		"$",
		"|",
		">",
		">>",
		"<",
		"<<",
		"&",
		"; () {}",
		"NOTOKEN",
	};

	el = line;
	printf("___________________LINE______________________\n");
	while (el != NULL)
	{
		printf("[%2d] type : %2d %8s [c] %c   ", el->index, el->type,
			tokentype_str[el->type - 1], el->c);
		printf("[dq] %2d   ", el->dq);
		printf("[sq] %2d \n", el->sq);
		el = el->next;
	}
	printf("\n");
}

void	print_t_token(t_bigshell *data)
{
	t_token		*el;
	// const char	*aim_str[] = {
	// 	"REDIR",
	// 	"CMD",
	// 	"BUILTIN",
	// 	"PIPEX",
	// };

	el = data->token;
	dprintf(2, "__________________TOKEN________________________\n");
	while (el)
	{
		printf("[%2d] ", el->index);
		printf("tok %2d ", el->type);
		printf(": %20s ", el->value);
		printf("→ %2d\n", el->aim);
		// printf("%8s\n", aim_str[el->aim - 20]);
		el = el->next;
	}
}

void	print_simple_cmd(t_bigshell *data)
{
	t_simple_cmd		*el;

	el = data->simple_cmd;
	printf("__________________SIMPLE_________________________\n");
	while (el != NULL)
	{
		dprintf(2, "[%2d] cmd : %8s\t\tbuiltin y/n %d\n", el->idx,
			el->cmd, el->builtin);
		dprintf(2, "\tfd_in   = %2d\tin_file  : %s\n", el->fd_in, el->in_file);
		dprintf(2, "\tfd_out  = %2d\tout_file : %s\n", el->fd_out, el->out_file);
		el = el->next;
	}
	printf("_________________________________________________\n");
}

/*
void	print_redir(t_bigshell *data)
{
	t_redir		*el;
	const char	*toktype[] = {
		"WORD",
		"DQUOTE",
		"SQUOTE",
		"\n",
		"BLANK",
		"$",
		"|",
		">",
		">>",
		"<",
		"<<",
		"&",
		"; () {}",
		"NOTOKEN",
	};

	el = data->in_out;
	printf("__________________REDIR________________________\n");
	while (el)
	{
		printf("[%2d] %2d %2s ", el->idx, el->type, toktype[el->type - 1]);
		printf(": %15s → fd %d & with cmd n°%d \n", el->file, el->fd,
			el->with_cmd_nb);
		el = el->next;
	}
}
*/