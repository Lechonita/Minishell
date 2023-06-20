/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 12:02:32 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "error.h"

# include <stdio.h>
# include <stdlib.h> 	//exit
# include <unistd.h> 	//access, dup, dup2, execve, fork, pipe, unlink
# include <sys/types.h> //wait, waitpid
# include <sys/wait.h> 	//wait, waitpid
# include <errno.h>
# include <string.h>	//strerror
# include <fcntl.h>		//open
# include <stdint.h>
# include <limits.h> 	// INT_MIN (-2147483648) INT_MAX (2147483647)
# include <signal.h>	// signal
# include <sys/stat.h>	// TBD
# include <assert.h>
# include <sys/prctl.h>
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# define TYPE_SEPARATOR 1 
# define TYPE_OPERATOR 2
# define TYPE_WORD 3
# define TYPE_INTEGER 4
# define TYPE_DOUBLE_QUOTES 5
# define TYPE_SINGLE_QUOTES 6
# define TYPE_BLANK 7

typedef struct s_exec
{
	int				index;
	int				fd_in;
	int				fd_out;
	char			*cmd;
	struct s_exec	*next;
}	t_exec;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_argv
{
	int				index;
	int				type;
	char			*value;
	struct s_argv	*next;
}	t_argv;

typedef struct s_line
{
	int				i;
	int				type;
	int				dq;		// if 0, inexistant. if 1, c'est ouvert. if 2, c'est ferme
	int				sq;		// if 0, inexistant. if 1, c'est ouvert. if 2, c'est ferme
	char			c;
	struct s_line	*next;
}	t_line;

typedef struct s_bigshell
{
	char			**history;
	t_argv			*argv;
	t_env			*env;
	t_exec			*exec;
}	t_bigshell;

/***********************************************************/
/*                          MAIN                           */
/***********************************************************/

/* MAIN */
void	ft_readline(t_bigshell *data);

/***********************************************************/
/*                       ENVIRONMENT                       */
/***********************************************************/

/*  ENV INIT */
t_env	*env_last(t_env *new);
void	env_addback(t_env *new, t_env *env);
t_env	*env_new(char *env);
void	init_env(t_bigshell *data, char **env);
// void	display_env_struct(t_bigshell *data);

/* ENV FIND VALUES */
// char	*ft_strndup(const char *src, size_t n);
char	*get_env_value(char *env);
int		find_equal(char *env);
char	*get_env_name(char	*env);

/***********************************************************/
/*                       HISTORY                           */
/***********************************************************/
void	init_history(t_bigshell *data);

/***********************************************************/
/*                        ARGUMENTS                        */
/***********************************************************/

/* ARGV INIT */
// t_argv	*argv_last(t_argv	*argv);
// void	argv_addback(t_argv *argv, t_argv *new);
// t_argv	*argv_new(char *line, int i);

/* ARGV FIND VALUES */
// int		get_argv_type(char *token);
// char	*get_argv_value(char *line, int nb, int i, int j);
void	get_argv_value_type(t_argv *new, char *line, int tkn_nb);
int		ft_determine_token(t_argv *new, char *line, int i);

/* ARGV ASSIGN */
int		ft_quotes(t_argv *new, char *line, char limiter, int i);

void	display_argv_struct(t_bigshell *data);

/***********************************************************/
/*                           FREE                          */
/***********************************************************/

/* FREE STRUCT*/
void	ft_free_env(t_bigshell *data);
void	ft_free_argv(t_bigshell *data);
void	ft_free_history(t_bigshell *data);
void	ft_free_all(t_bigshell *data);

/***********************************************************/
/*                           ERROR                         */
/***********************************************************/

/* error */
void	ft_exit(int err_no, char *msg);
void	print_strs(char **strs);

#endif
