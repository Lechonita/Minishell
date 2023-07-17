/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/17 09:38:38 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "builtins.h"
# include "env.h"
# include "error.h"
# include "exec.h"
# include "expander.h"
# include "exec.h"
# include "input.h"
# include "lexer.h"
# include "parser.h"
# include "redirection.h"

/* MAIN */
void	ft_readline(t_bigshell *data, char *env[]);

/***********************************************************/
/*                          UTILS                          */
/***********************************************************/

char	*free_strjoin(char *to_free, char *buf);
char	*ft_strjoin_bis(char *s1, char *s2, char *to_add);

/* FREE STRUCT*/
void	free_strs(char **strs);
void	ft_free_line(t_line **line);
void	ft_free_env(t_env **env);
void	ft_free_token(t_token **token);
void	ft_free_cmd(t_cmd **cmd);
void	ft_free_exec(t_exec **exec);
void	ft_free_history(t_bigshell *data);
void	ft_free_redirection(t_redir **redir);
void	free_all(t_bigshell *data);

/* PRINT ERROR */
void	ft_exit(int err_no, char *msg);
void	error_execve(t_bigshell *data);
void	msg_not_found(char *msg, char *str);
void	error_not_found(t_bigshell *data, char *msg, char *str);

/* PRINT FUNCTION */
void	print_strs(char **strs);
void	print_cmd_lst(t_bigshell *data);
void	print_t_line(t_bigshell *data);
void	print_t_token(t_bigshell *data);
void	print_redir(t_bigshell *data);
void	print_exec(t_bigshell *data);
void	display_env_struct(t_bigshell *data);
void	print_history_lst(t_bigshell *data);

#endif
