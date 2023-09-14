/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:47:50 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/14 14:05:49 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define W_NO_ENV "\t No environment\n"
# define IS_DIRECTORY ": Is a directory\n"
# define W_EXECVE "\t Failure with execve /\n"
# define HOME_NOT_SET "Minishell: HOME not set\n"
# define PERM_DENIED "Minishell: Permission denied: "
# define W_SPLIT_CMD "\t Failure in split commands\n"
# define OLDPWD_NOT_SET "Minishell: OLDPWD not set\n"
# define W_LST_CMD "\t Failure in creating cmds lst\n"
# define CMD_NOT_FOUND "Minishell: command not found: "
# define W_LST_LINE "\t Failure in creating line lst\n"
# define W_LST_TOK "\t Failure in creating token lst\n"
# define W_EXIT_ARG_NUM ": numeric argument required\n"
# define W_CD_ARG "Minishell: cd: too many arguments\n"
# define W_SPLIT_ENV "\t Failure spliting environment\n"
# define W_HD_OPEN "\t Failure in open/creat here_doc\n "
# define W_LST_CMD_DUP "\t Failure in duplicate cmd name\n"
# define W_EXIT_ARG "Minishell: exit: too many arguments\n"
# define W_POINT_POINT "Minihsell: ..: command not found\n"
# define W_POINT "Minihsell: .: filename argument required\n"
# define W_LST_RED "\t Failure in creating redirection lst\n"
# define FILE_NOT_FOUND "Minishell: No such file or directory: "
# define W_LST_RED_TYP "\t Failure in duplicate redirection type\n"
# define W_LST_RED_FIL "\t Failure in duplicate redirection file name\n"
# define W_PIPE "Minishell: syntax error near unexpected token `pipe'\n"
# define W_BUILT_ENV "\t Env: too many arguments - not in subject scope \n"
# define W_REDIR_TWOG "Minishell: syntax error near unexpected token `>'\n"
# define W_REDIR_TWOL "Minishell: syntax error near unexpected token `<'\n"
# define W_REDIR_THREEG "Minishell: syntax error near unexpected token `>>'\n"
# define W_REDIR_THREEL "Minishell: syntax error near unexpected token `<<'\n"
# define W_REDIR_ONE "Minishell: syntax error near unexpected token `newline'\n"
# define W_HD_CTRL_D "warning: here-document delimited by end-of-file (wanted `"

#endif