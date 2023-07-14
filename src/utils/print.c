/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:51:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/14 18:32:34 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("[%2d] %s\n", i, strs[i]);
		i++;
	}
}

void	print_cmd_lst(t_bigshell *data)
{
	t_cmd	*el;
	int		j;

	el = data->exec->cmd;
	while (el != NULL)
	{
		dprintf(2, "path : %s, command n°%d → %s\n", el->cmd,
			el->idx_cmd, el->cmd_arg[0]);
		j = 0;
		while (el->cmd_arg[j])
		{
			dprintf(2, "\t\t args [%d] → %s\n", j, el->cmd_arg[j]);
			j++;
		}
		el = el->next;
	}
}

void	print_t_line(t_bigshell *data)
{
	t_line	*el;
	const char	*tokentype_str[] =
	{
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
		printf("[%2d] ", el->index);
		printf("type : %2d  %8s ", el->type, tokentype_str[el->type - 1]);
		// printf("[dq] %2d ", el->dq);
		// printf("[sq] %2d ", el->sq);
		printf("[c] %c\n", el->c);
		el = el->next;
	}
}
// printf("_______________________________________________\n");

void	print_t_token(t_bigshell *data)
{
	t_token	*el;
	const char	*aim_str[] =
	{
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
	t_redir	*el;
	const char	*tokentype_str[] =
	{
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
		printf("[%2d] ", el->idx);
		printf(" %2d %2s ", el->type, tokentype_str[el->type - 1]);
		printf(": %15s ", el->file);
		printf("→ fd %d\n", el->fd);
		// printf("& perm %d\n", el->exec_perm);
		el = el->next;
	}
	printf("\n");
}

void	print_exec(t_bigshell *data)
{
	t_exec	*el;

	el = data->exec;
	printf("__________________EXEC_________________________\n");
	dprintf(2, "fd_in    = %d 	fd_out = %d\n", el->fd_in, el->fd_out);
	dprintf(2, "nb_cmd   = %d\n", el->nb_cmd);
	dprintf(2, "in_file  : %s\nout_file : %s\n", el->in_file, el->out_file);
	dprintf(2, "heredoc  = %d\nredir/no_redir %d\n", el->here_doc, data->redir_or_not);
	print_cmd_lst(data);
	printf("\n_______________________________________________\n");
}

/* fonction qui permet d'afficher t_env
	(equivalent de la commande "env" ou "printenv" dans le terminal) */
void	display_env_struct(t_bigshell *data)
{
	t_env	*el;

	// if (!data->env)
	// 	ft_exit(EXIT_FAILURE, "No env to display\n");
	el = data->env;
	while (el != NULL)
	{
		printf("[%2d] %s=%s\n", el->index, el->name, el->value);
		el = el->next;
	}
}
