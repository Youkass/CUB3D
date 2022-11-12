
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggane <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 10:38:58 by ggane             #+#    #+#              #
#    Updated: 2016/12/19 01:04:52 by ggane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libminiaudio.a
CC=gcc
RM=rm -f
LDFLAGS=-L.
LDLIBS=-lminiaudio
SRC = extras/miniaudio_split/miniaudio.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c
		$(CC) -lpthread -ldl -c $< -o ${<:.c=.o}

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean clean
