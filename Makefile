###############################################################################
#__________________________Makefile for Minishell_____________________________#
###############################################################################

NAME = minishell

############################### Compiler #######################################

FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address 
CC = gcc

############################### LIBFT ##########################################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS += -L $(LIBFT_DIR) #-lft

############################### Includes #######################################

INC_DIR = ./inc
INCLUDES += -I $(INC_DIR)
INCLUDES += -I $(LIBFT_DIR)/includes

############################### Headers ########################################

HEADER += inc/minishell.h
HEADER += inc/error.h
# HEADER += ./libft/includes/libft.h
# HEADER += ./libft/includes/get_next_line.h

vpath %.h $(INC_DIR)

############################### Path Sources ###################################

SRC_DIR = ./src

############################### Sources ########################################

SRC += main.c 
SRC += env_init.c
SRC += env_find_values.c
SRC += prompt.c
SRC += free_struct.c
SRC += argv_init.c
SRC += argv_find_values.c
SRC += argv_assign.c
SRC += print_error.c
SRC += history_init.c
SRC += line_init.c
SRC += type.c
SRC += type2.c
# SRC += get_next_line.c // a retirer, doublon avec ajout du gnl dans la libft

vpath %.c $(SRC_DIR)

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

all: $(NAME)

$(LIBFT):
	@make --no-print-directory all -C $(LIBFT_DIR)
	@echo "\n	⤳$(GREEN) Created libft 🎇\n$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ) : $(OBJ_DIR)/%.o: %.c | $(LIBFT) $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) $(INCLUDES) -o $(NAME) -lreadline
	@echo "\n	⤳$(GREEN) Created $(NAME) ✨\n$(DEF_COLOR)"


# art:
# 	@echo "$(RED)  __  __   _           _    _____   _              _   _ $(END)"
# 	@echo "$(RED) |  \/  | (_)         (_)  / ____| | |            | | | |$(END)"
# 	@echo "$(RED) | \  / |  _   _ __    _  | (___   | |__     ___  | | | |$(END)"
# 	@echo "$(RED) | |\/| | | | | '_ \  | |  \___ \  | '_ \   / _ \ | | | |$(END)"
# 	@echo "$(RED) | |  | | | | | | | | | |  ____) | | | | | |  __/ | | | |$(END)"
# 	@echo "$(RED) |_|  |_| |_| |_| |_| |_| |_____/  |_| |_|  \___| |_| |_|$(END)"
# 	@echo "$(RED)                                                         $(END)"

norm:
	@norminette $(HEADER) 
	@norminette $(SRC_DIR)

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

.PHONY: all clean fclean re

############################### Color ##########################################

END=\033[0m
RED=\033[5;31m
LRED=\033[38;5;124m
GREEN=\033[1;5;32m
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