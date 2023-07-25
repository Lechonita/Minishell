/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:47:50 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/25 17:01:07 by bebigel          ###   ########.fr       */
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
# define W_LST_CMD "\t Failure in creating cmds lst\n"
# define W_LST_RED "\t Failure in creating redirection lst\n"
# define W_LST_CMD_DUP "\t Failure in duplicate cmd name\n"
# define W_LST_RED_TYP "\t Failure in duplicate redirection type\n"
# define W_LST_RED_FIL "\t Failure in duplicate redirection file name\n"
# define W_SPLIT_CMD "\t Failure in split commands\n"
# define W_EXIT_ARG "Minishell: exit: too many arguments\n"
# define W_EXIT_ARG_NUM ": numeric argument required\n"
# define W_MALLOC "\t Failure in malloc\n"

// # define W_ENV "\t Environment error\n"
// # define W_JOIN_PATH "\t Failure in joining path with / \n"
// # define W_ENV_PATH "env PATH is empty\n"
// # define W_SPLIT_ENV "\t Failure in split environment\n"

// # define W_STRDUP "\t Failure in duplicate str\n "

#endif