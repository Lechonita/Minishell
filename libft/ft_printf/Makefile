NAME = libftprintf.a

SRCS +=	ft_printf.c
SRCS +=	ft_conv.c
SRCS +=	ft_countone.c
SRCS +=	ft_countbis.c
SRCS +=	ft_write.c

OBJS = $(SRCS:.c=.o)

HEADER = ft_printf.h \

GNL_PATH = ../get_next_line

GCC = gcc -Wall -Werror -Wextra

RM = rm -rf

# PROGRESS BAR
NB_OBJ = ${words ${SRCS}}
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
	@${GCC} -c $< -o ${<:.c=.o}
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

$(NAME) : $(OBJS)
	@make -sC $(GNL_PATH)
	@cp $(GNL_PATH)/gnl.a ./$(NAME)
	@ar rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	@make -sC $(GNL_PATH) clean
	@$(RM) $(OBJS)

fclean : clean
	@make -sC $(GNL_PATH) fclean
	@$(RM) $(NAME)

re : fclean all

PHONY : all clean fclean re

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