NAME = gnl.a

SRCS = get_next_line.c \
	get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

LIBFT_PATH = ../libft

GCC = gcc 

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

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

.c.o:
	@${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

$(NAME) : $(OBJS)
		@make -sC $(LIBFT_PATH)
		@cp $(LIBFT_PATH)/libft.a ./$(NAME)
		@ar rcs $(NAME) $(OBJS)

all : $(NAME)

clean : 
		@make -sC $(LIBFT_PATH) clean
		@$(RM) $(OBJS)

fclean : clean 
		@make -sC $(LIBFT_PATH) fclean
		@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

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