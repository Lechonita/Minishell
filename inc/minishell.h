/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/06 11:45:48 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "error.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "input.h"
# include "exec.h"
# include "expander.h"

/* MAIN */
void	ft_readline(t_bigshell *data, char *env[]);

/***********************************************************/
/*                          UTILS                          */
/***********************************************************/

/* FREE STRUCT*/
void	free_strs(char **strs);
void	ft_free_line(t_line **line);
void	ft_free_env(t_env **env);
void	ft_free_token(t_token **token);
void	ft_free_cmd(t_cmd **cmd);
void	ft_free_exec(t_exec **exec);
void	ft_free_history(t_bigshell *data);
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
void	display_env_struct(t_bigshell *data);
void	print_history_lst(t_bigshell *data);

#endif
