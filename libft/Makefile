# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lechon <lechon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 12:22:06 by bebigel           #+#    #+#              #
#    Updated: 2023/06/06 16:55:34 by lechon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isascii.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_substr.c \
	ft_strtrim.c \
	ft_strjoin.c \
	ft_itoa.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_strmapi.c \
	ft_putnbr_fd.c \
	ft_split.c \
	ft_printf.c \
	ft_write.c \
	ft_countone.c \
	ft_countbis.c \
	ft_conv.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

FLAG = -Wall -Werror -Wextra

OBJ=$(SRC:.c=.o)

# Colors
END=\033[0m
RED=\033[5;31m
LRED=\033[38;5;124m
GREEN=\033[1;5;32m
LGREEN=\033[38;5;22m
BLUE=\033[1;34m
LBLUE=\033[1;94m
GREY=\033[1;3;90m
DEF_COLOR =	\033[0;39m

# PROGRESS BAR

NB_OBJ = ${words ${OBJ}}

COUNTER = 1

PROGRESS = 0

DONE = 100

SPACE = 0

FILL = 0

EMPTY = 0

CLEAR = \033[2K

define PROGRESS_BAR
	$(eval PROGRESS=$(shell echo $$(($(COUNTER) * 100 / $(NB_OBJ)))))
	$(eval DONE=$(shell echo $$(($(PROGRESS) * 30 / 100))))
	$(eval SPACE=$(shell echo $$((30 - $(DONE)))))
	$(eval FILL=$(shell printf "%*s" ${DONE} | sed 's/ /▶/g'))
	$(eval EMPTY=$(shell printf "%*s" ${SPACE} | sed 's/ /◀/g'))
	printf "\r${CLEAR}$(BLUE)Compile : $(LGREEN)${FILL}$(LRED)${EMPTY} $(BLUE)%3d%%$(END) %s.c" ${PROGRESS} $1
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAG) -c $(SRC)
	ar rcs $(NAME) $(OBJ)

.c.o: 
	@echo -n "$(_CYAN).$(_END)"
	gcc $(FLAG) -c $< -o $@
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
