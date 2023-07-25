/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/25 18:16:47 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_cmd_lst(t_bigshell *data)
{
	t_cmd	*el;
	int		j;

	el = data->exec->cmd;
	while (el != NULL)
	{
		dprintf(2, "cmd n°%d → %s \tbuiltin %d\n", el->idx_cmd,
			el->cmd_arg[0], el->builtin);
		j = 0;
		while (el->cmd_arg[j])
		{
			dprintf(2, "\t args [%d] → %s\n", j, el->cmd_arg[j]);
			j++;
		}
		el = el->next;
	}
}

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
	const char	*aim_str[] = {
		"REDIR",
		"CMD",
		"BUILTIN",
		"PIPEX",
	};

	el = data->token;
	printf("__________________TOKEN________________________\n");
	while (el)
	{
		printf("[%2d] ", el->index);
		printf("tok %2d ", el->type);
		printf(": %20s ", el->value);
		printf("→ %2d %8s\n", el->aim, aim_str[el->aim - 20]);
		el = el->next;
	}
}

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
		printf(": %15s → fd %d\n", el->file, el->fd);
		el = el->next;
	}
}

void	print_exec(t_bigshell *data)
{
	t_exec	*el;

	el = data->exec;
	printf("__________________EXEC_________________________\n");
	dprintf(2, "fd_in    = %d\tfd_out   = %d\n", el->fd_in, el->fd_out);
	dprintf(2, "nb_cmd   = %d\theredoc  = %d\tno/redir =%d\n", el->nb_cmd,
		el->here_doc, data->redir_or_not);
	dprintf(2, "in_file  : %s\nout_file : %s\n", el->in_file, el->out_file);
	print_cmd_lst(data);
	printf("_______________________________________________\n");
}

/*
void	print_t_line(t_bigshell *data)
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

	el = data->line;
	while (el != NULL)
	{
		printf("[%2d] type : %2d %8s [c] %c\n", el->index, el->type,
			tokentype_str[el->type - 1], el->c);
		el = el->next;
	}
}
*/