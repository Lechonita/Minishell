/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:47:50 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/26 12:18:31 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define W_NO_ENV "\t No environment\n"
# define W_SPLIT_ENV "\t Failure spliting environment\n"

// # define W_ARG "\t Wrong argument number\n"
// # define W_ENV "\t Environment error\n"
// # define W_JOIN_PATH "\t Failure in joining path with / \n"
// # define W_ENV_PATH "env PATH is empty\n"
// # define W_SPLIT_ENV "\t Failure in split environment\n"
// # define W_SPLIT_CMD "\t Failure in split commands\n"
// # define W_CMDS "\t Failure in getting commands \n"
// # define W_NEW_LST "\t Failure in creating new lst\n"
// # define W_LST "\t Failure in creating cmds lst\n"
// # define W_EXECVE "\t Failure with execve /\n"
// # define W_STRDUP "\t Failure in duplicate str\n "
# define W_HD_OPEN "\t Failure in open/creat here_doc\n "
# define CMD_NOT_FOUND "bash: command not found: "
# define PERM_DENIED "bash: Permission denied: "
# define FILE_NOT_FOUND "bash: No such file or directory: "

#endif