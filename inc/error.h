/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:47:50 by bebigel           #+#    #+#             */
/*   Updated: 2023/09/12 11:52:04 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define W_NO_ENV "\t No environment\n"
# define W_SPLIT_ENV "\t Failure spliting environment\n"
# define W_EXECVE "\t Failure with execve /\n"
# define W_HD_OPEN "\t Failure in open/creat here_doc\n "
# define CMD_NOT_FOUND "Minishell: command not found: "
# define PERM_DENIED "Minishell: Permission denied: "
# define FILE_NOT_FOUND "Minishell: No such file or directory: "
# define W_LST_TOK "\t Failure in creating token lst\n"
# define W_LST_LINE "\t Failure in creating line lst\n"
# define W_LST_CMD "\t Failure in creating cmds lst\n"
# define W_LST_RED "\t Failure in creating redirection lst\n"
# define W_LST_CMD_DUP "\t Failure in duplicate cmd name\n"
# define W_LST_RED_TYP "\t Failure in duplicate redirection type\n"
# define W_LST_RED_FIL "\t Failure in duplicate redirection file name\n"
# define W_SPLIT_CMD "\t Failure in split commands\n"
# define W_EXIT_ARG "Minishell: exit: too many arguments\n"
# define W_EXIT_ARG_NUM ": numeric argument required\n"
# define HOME_NOT_SET "Minishell: HOME not set\n"
# define OLDPWD_NOT_SET "Minishell: OLDPWD not set\n"
# define W_CD_ARG "Minishell: cd: too many arguments\n"
# define W_BUILT_ENV "\t Env: too many arguments - not in subject scope \n"
# define W_REDIR_ONE "Minishell: syntax error near unexpected token `newline'\n"
# define W_PIPE "Minishell: syntax error near unexpected token: pipe\n"
# define IS_DIRECTORY ": Is a directory\n"

// # define W_ENV "\t Environment error\n"
// # define W_JOIN_PATH "\t Failure in joining path with / \n"
// # define W_ENV_PATH "env PATH is empty\n"
// # define W_SPLIT_ENV "\t Failure in split environment\n"

// # define W_STRDUP "\t Failure in duplicate str\n "

#endif