/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/14 14:15:11 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "env.h"
# include "exec.h"
# include "error.h"
# include "input.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "expander.h"
# include "redirection.h"

/* GLOBAL VARIABLE */

typedef struct s_global
{
	int	exit_status;
	int	heredoc;
	int	nb_cmd;
}				t_global;

extern t_global	g_global;

/* MAIN */
void	ft_readline(t_bigshell *data);

/***********************************************************/
/*                          UTILS                          */
/***********************************************************/

char	*free_strjoin(char *to_free, char *buf);

/* FREE STRUCT*/
void	free_strs(char **strs);
void	ft_free_env(t_env **env);
void	free_all(t_bigshell *data);
void	ft_free_line(t_line **line);
void	ft_free_token(t_token **token);
void	ft_free_history(t_bigshell *data);
void	ft_free_redirection(t_redir **redir);
void	reset_prompt(t_bigshell *data, char *input);
void	ft_free_simple_cmd(t_simple_cmd **simple_cmd);

/* PRINT ERROR */
int		ft_error(int err_no, char *msg);
int		is_directory(char *msg, char *str);
int		msg_not_found(char *msg, char *str);
void	error_execve(t_bigshell *data, char *msg);
void	error_not_found(t_bigshell *data, char *msg, char *str);

/* PRINT FUNCTION */
void	print_strs(char **strs);
void	print_t_line(t_line *line);
void	print_redir(t_bigshell *data);
void	print_t_token(t_bigshell *data);
void	print_simple_cmd(t_bigshell *data);
void	print_history_lst(t_bigshell *data);
void	display_env_struct(t_bigshell *data);

#endif
