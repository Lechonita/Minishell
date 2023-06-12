#################
#				#
#	 Project	#
#				#
#################
NAME = minishell


FLAG = -Wall -Wextra -Werror
FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
CC = gcc

#	Sources		#
SRC_DIR = src/
SRC = main.c env_init.c env_find_values.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

#	Objects		#
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#	libft		#
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

#	Includes	#
INC = -I ./inc/ \
	-I ./libft/

HDR = inc/minishell.h

# PROGRESS BAR
NB_OBJ = ${words ${OBJ}}
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

#		MiniShell		#
all: art $(OBJ_DIR) $(LIBFT) $(NAME)

art:
	@echo "$(RED)  __  __   _           _    _____   _              _   _ $(END)"
	@echo "$(RED) |  \/  | (_)         (_)  / ____| | |            | | | |$(END)"
	@echo "$(RED) | \  / |  _   _ __    _  | (___   | |__     ___  | | | |$(END)"
	@echo "$(RED) | |\/| | | | | '_ \  | |  \___ \  | '_ \   / _ \ | | | |$(END)"
	@echo "$(RED) | |  | | | | | | | | | |  ____) | | | | | |  __/ | | | |$(END)"
	@echo "$(RED) |_|  |_| |_| |_| |_| |_| |_____/  |_| |_|  \___| |_| |_|$(END)"
	@echo "$(RED)                                                         $(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR)
	@$(CC) $(FLAGS) -c $< -o $@ $(INC)
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

#		LIBFT		#
$(LIBFT):
	@make -sC $(LIBFT_DIR)
	@echo "\n	⤳$(GREEN) Created $(LIBFT_DIR) 🎇\n$(DEF_COLOR)"

#		Rules		#
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(INC) -o $(NAME)
	@echo "\n	⤳$(GREEN) Created $(NAME) ✨\n$(DEF_COLOR)"

bonus: all

norm:
	@norminette $(SRCS) $(HDR)

clean:
	@echo "$(HGREY)Removing .o object files...$(END)"
	@make clean -sC $(LIBFT_DIR)
	@echo "$(HGREY)Removing libft...$(END)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(HGREY)Removing Pipex...$(END)"
	@make fclean -sC $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "	⤳$(GREY) All cleaned 🌊\n$(END)"

re: fclean all

.PHONY: all clean fclean re bonus

######################### Color #########################
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