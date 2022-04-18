# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: anonymous <anonymous@student.codam.nl>       +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/14 23:04:48 by anonymous     #+#    #+#                  #
#    Updated: 2022/04/18 19:28:25 by alpha         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=ft_select

CC=gcc
FLAGS=-Wall -Werror -Wextra
DEBUG_FLAGS=-g -fsanitize=address
SRC= \
	lib/memset.c 	\
	lib/strcmp.c	\
	lib/strlen.c	\
	src/caches.c	\
	src/ft_select.c	\
	src/ft_select.h	\
	src/init.c		\
	src/keys.c		\
	src/printer.c	\
	src/signal.c	\
	src/writer.c
LIBS=-I src/
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(LIBS) $(SRC) -o $(NAME) -ltermcap

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LIBS) $(SRC) -o $(NAME) -ltermcap
