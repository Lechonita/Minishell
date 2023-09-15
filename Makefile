###############################################################################
#__________________________Makefile for Minishell_____________________________#
###############################################################################

NAME = minishell

############################### Compiler #######################################

FLAGS = -Wall -Wextra -Werror

ifeq ($(debug), true)
	FLAGS += -fsanitize=address
endif

CC = cc

############################### LIBFT ##########################################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS += -L $(LIBFT_DIR) -lft

############################### Includes #######################################

INC_DIR = ./inc
INCLUDES += -I $(INC_DIR)
INCLUDES += -I $(LIBFT_DIR)/includes

############################### Headers ########################################


HEADER += inc/minishell.h
HEADER += inc/builtins.h
HEADER += inc/env.h
HEADER += inc/error.h
HEADER += inc/exec.h
HEADER += inc/expander.h
HEADER += inc/input.h
HEADER += inc/lexer.h
HEADER += inc/parser.h
HEADER += inc/redirection.h
HEADER += inc/struct.h

vpath %.h $(INC_DIR)

############################### Path Sources ###################################

SRC_DIR = ./src
BUILTINS_DIR = ./src/builtins
ENV_DIR = ./src/env
EXEC_DIR = ./src/exec
EXPANDER_DIR = ./src/expander
TERM_DIR = ./src/input
LEXER_DIR = ./src/lexer
PARSER_DIR = ./src/parser
PIPE_DIR = ./src/pipe
REDIR_DIR = ./src/redirection
UTILS_DIR = ./src/utils

############################### Sources ########################################

SRC += main.c 

#	Builtins functions
SRC += builtins.c
SRC += cd.c
SRC += cd_utils.c
SRC += echo.c
SRC += env.c
SRC += exit.c 
SRC += export.c
SRC += pwd.c
SRC += unset.c

#	Env functions
SRC += env_init.c
SRC += path_handle.c
SRC += handle_export.c
SRC += export_utils.c

# 	Exec functions
SRC += executor.c
SRC += simple_cmd_exec.c

#	Expander functions
SRC += dollar_add_value.c
SRC += dollar_expansion.c
SRC += dollar_utils.c
SRC += dollar.c

#	Input functions
SRC += prompt.c
SRC += signal.c
SRC += signal_here_doc.c

#	Lexer functions
SRC += check_caracter.c
SRC += find_token_type.c
SRC += flag_quotes.c
SRC += line_init.c
SRC += quote_del.c
SRC += token_find.c
SRC += token_init.c
SRC += token_type.c
SRC += token_type_bis.c

#	Parser functions
SRC += parser_job.c
SRC += parser_utils.c
SRC += init_simple_cmd.c
SRC += handle_cmd.c
SRC += aim_utils.c

#	Redirection functions
SRC += handle_redir.c
SRC += init_redir.c
SRC += redir_utils.c
SRC += io_in_simple_cmd.c

#	Utils functions
SRC += free_struct.c
SRC += free_struct_bis.c
SRC += error.c
SRC += print.c
SRC += print_bis.c

vpath %.c $(SRC_DIR)
vpath %.c $(TERM_DIR)
vpath %.c $(REDIR_DIR)
vpath %.c $(UTILS_DIR)
vpath %.c $(BUILTINS_DIR)
vpath %.c $(EXEC_DIR)
vpath %.c $(PARSER_DIR)
vpath %.c $(ENV_DIR)
vpath %.c $(LEXER_DIR)
vpath %.c $(EXPANDER_DIR)
vpath %.c $(PIPE_DIR)

############################### Objects ########################################

OBJ_DIR = ./obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

############################### Progress Ber ###################################

NB_OBJ = ${words ${SRC}}
COUNTER = 1
PROGRESS = 0
DONE = 100
SPACE = 0
FILL = 0
EMPTY = 0

define PROGRESS_BAR
	$(eval PROGRESS=$(shell echo $$(($(COUNTER) * 100 / $(NB_OBJ)))))
	$(eval DONE=$(shell echo $$(($(PROGRESS) * 30 / 100))))
	$(eval SPACE=$(shell echo $$((30 - $(DONE)))))
	$(eval FILL=$(shell printf "%*s" ${DONE} | sed 's/ /▶/g'))
	$(eval EMPTY=$(shell printf "%*s" ${SPACE} | sed 's/ /◀/g'))
	printf "\r${CLEAR}$(BLUE)Compile : $(LGREEN)${FILL}$(LRED)${EMPTY} $(BLUE)%3d%%$(END) %s.c " ${PROGRESS} $1
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

############################### Rules ##########################################

all: $(NAME) art

$(LIBFT):
	@make --no-print-directory all -C $(LIBFT_DIR)
	@echo "\n	⤳$(GREEN) Created libft 🎇\n$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ) : $(OBJ_DIR)/%.o: %.c | $(LIBFT) $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) $(INCLUDES) -o $(NAME) -lreadline -lncurses
	@echo "\n	⤳$(GREEN) Created $(NAME) ✨\n$(DEF_COLOR)"

art:
	@./banner.sh

norm:
	@norminette src/*/*.c
	@norminette inc/*.h

leaks: $(NAME) art
	@printf "$(GREY)Checking leaks with valgrind...\n$(END)"
	@sleep 0.5
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=./.readline_supp -q ./$(NAME)
# --gen-suppressions=all --gen-suppressions=all --log-file="valou"

clean:
	@echo "$(HGREY)Removing .o object files...$(END)"
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(HGREY)Removing libft...$(END)"
	@rm -f $(LIBFT)
	@echo "$(HGREY)Removing MiniShell...$(END)"
	@rm -f $(NAME)
	@echo "	⤳$(GREY) All cleaned 🌊\n$(END)"

re: fclean all

.PHONY: all clean fclean re leaks norm

############################### Color ##########################################

END=\033[0m
RED=\033[1;31m
LRED=\033[38;5;124m
GREEN=\033[1;32m #\033[1;5;32m
LGREEN=\033[38;5;22m
BLUE=\033[1;34m
LBLUE=\033[1;94m
GREY=\033[1;3;90m
HGREY=\033[38;5;235m
DEF_COLOR =	\033[0;39m
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
CLEAR = \033[2K
SAVE = "\033[s"
RESTORE = "\033[u"
