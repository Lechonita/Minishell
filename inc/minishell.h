/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:31 by bebigel           #+#    #+#             */
/*   Updated: 2023/07/03 17:33:25 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "error.h"
# include "./lexer.h"
// # include "env.h"

# include <stdio.h>
# include <stdlib.h> 			//exit
# include <unistd.h> 			//access, dup, dup2, execve, fork, pipe, unlink
# include <sys/types.h> 		//wait, waitpid
# include <sys/wait.h> 			//wait, waitpid
# include <errno.h>
# include <string.h>			//strerror
# include <fcntl.h>				//open
# include <stdint.h>
# include <limits.h> 			// INT_MIN (-2147483648) INT_MAX (2147483647)
# include <signal.h>			// signal
# include <sys/stat.h>			// TBD
# include <assert.h>
# include <sys/prctl.h>
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include <termios.h>			//configuration terminal
# include <term.h>				//terminal capabilities
# include <curses.h>			//terminal capabilities

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

// typedef struct s_builtin
// {
// 	char	*name;
// 	int		(*func)(t_bigshell *data, int cmd_ac, char *cmd_av[]);
// }	t_builtin;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_arg;
	int				idx_cmd;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_redir
{
	int				type;		// 0 = <, 1 = >, 2 = >>, 3 = <<
	char			*file;		// file name
	char			*limiter;	// word for heredoc
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	int				nb_cmd;
	char			*in_file;
	char			*out_file;
	int				fd[FOPEN_MAX][2];
	int				here_doc;
	t_redir			*redir;
	t_cmd			*cmd;
}	t_exec;

typedef struct s_token
{
	int				index;
	int				type;
	int				aim;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_line
{
	int				index;
	int				type;
	int				dq;
	int				sq;
	char			c;
	struct s_line	*next;
}	t_line;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_bigshell
{
	char			**history;
	char			**env_paths;
	t_env			*env;
	t_line			*line;
	t_token			*token;
	t_exec			*exec;
}	t_bigshell;

/***********************************************************/
/*                          MAIN                           */
/***********************************************************/

/* MAIN */
void	ft_readline(t_bigshell *data, char *env[]);

/***********************************************************/
/*                           ENV                           */
/***********************************************************/

/*  ENV INIT */
char	*get_env_name(char	*env);
void	init_env(t_bigshell *data, char **env);

/* SEARCH GOOD PATH */
void	get_path(t_bigshell *data);
char	*find_path_to_cmd(t_bigshell *data, char *cmd);

/***********************************************************/
/*                  	   INPUT	                       */
/***********************************************************/

/* Test only */
void	save_line_for_test(t_bigshell *data, char *input, int count);

/* SIGNAL HANDLING */
void	catch_ctrl_d(t_bigshell *data, char *input);
void	ft_sig_int(int sig);
void	set_signal(void);

/* TERMINAL CAPABILITIES */
int		init_term(void);
int		ft_termcap(t_bigshell *data);

/* REDIRECTION */
void	handle_here_doc(t_bigshell *data, char *limiter);
void	redirection_append(t_bigshell *data);
void	redirection_left(t_bigshell *data);
void	redirection_right(t_bigshell *data);
void	redirection(t_bigshell *data);

/***********************************************************/
/*                  	   EXECUTOR	                       */
/***********************************************************/

/* EXEC INIT */
t_cmd	*init_cmd(t_bigshell *data);
void	init_exec(t_bigshell *data);

/* EXEC */
pid_t	execute_pipex(t_bigshell *data, char *env[], int pcss);
int		ft_waitpid(pid_t last_pid);
int		executor(t_bigshell *data, char *env[]);

/* PIPE UTILS */
void	open_pipe(t_bigshell *data);
void	close_pipe(t_bigshell *data);
void	handle_dup(t_bigshell *data, int pcss);

/***********************************************************/
/*                          PARSER                         */
/***********************************************************/

/* LINE INIT */
t_line		*line_last(t_line	*line);
void		line_addback(t_line *line, t_line *new);
t_line		*line_new(t_line *line, char c, int i);
void		init_line(t_bigshell *data, char *line);

/* FIND TYPE */
int			is_dollar(char c);
int			is_blank(char c);
int			is_single_quote(char c);
int			is_double_quote(char c);
int			is_integer(char c);
int			is_newline(char c);
int			is_ampersand(char c);
int			is_pipe(char c);
int			is_redir(char c);
int			is_separator(char c);
int			is_word(char c);
int			determine_type(char c);

/* FIND QUOTES */
int			find_closing_quote(t_line *line, int type);
void		convert_quotes(t_line *line, int type);
void		find_quotes(t_line *line);
void		flag_double_quotes(t_line *line);
void		flag_single_quotes(t_line *line);

/***********************************************************/
/*                          LEXER                          */
/***********************************************************/

/* FIND TOKENS */
void	token_rm_next(t_token *tok);
void	ft_create_token(t_bigshell *data, t_line *current, char *value, int pos);
void	find_tokens(t_bigshell *data);

/* GRAMMAR */
void	check_builtin(t_bigshell *data);
void	same_aim(t_bigshell *data);
void	add_arg_to_cmd(t_bigshell *data);
void	parser_job(t_bigshell *data);
void	apply_grammar(t_bigshell *data);

/***********************************************************/
/*                        EXPANDER                         */
/***********************************************************/

/* DOLLAR */

/* QUOTES FIND */
int			find_closing_quote(t_line *line, int type);
void		convert_quotes(t_line *line, int type);
void		find_quotes(t_line *line);

/* QUOTES OPEN */
void		delete_additional_quotes(t_line *line, int type);
void		assign_type_open_quotes(t_line *line);
int			determine_stop(t_line *line, int type);
void		input_open_quotes(t_line *line, char *input, int type);
void		get_rest_open_quotes(t_line *line, int type, char *prompt);
void		interpret_open_quotes(t_line *line, int type);

/* QUOTES POSITION */
// int			find_end_dq(t_line *line);
// int			find_start_dq(t_line *line);
// int			find_end_sq(t_line *line);
// int			find_start_sq(t_line *line);

/***********************************************************/
/*                  	  BUILTINS	                       */
/***********************************************************/

void	ft_env(t_bigshell *data);
void	ft_pwd(void);

/***********************************************************/
/*                          UTILS                          */
/***********************************************************/

/* FREE STRUCT*/
// void		ft_free_line_node(t_line *line);
void	ft_free_line(t_line **line);
void	ft_free_env(t_env **env);
void	ft_free_token(t_token **token);
void	ft_free_history(t_bigshell *data);
void	ft_free_all(t_bigshell *data);

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
