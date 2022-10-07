# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by tnard             #+#    #+#              #
#    Updated: 2022/10/06 14:27:24 by yobougre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/main.c\
				srcs/raycasting/raycasting_utils.c\
				srcs/raycasting/raycasting.c\
				srcs/raycasting/spritecasting.c\
				srcs/raycasting/player_casting.c\
				srcs/mlx_utils/mlx_utils.c\
				srcs/utils/singleton.c\
				srcs/utils/singleton_2.c\
				srcs/utils/malloc_hooks_enum.c\
				srcs/utils/key_hooks.c\
				srcs/utils/clock.c\
				srcs/utils/math.c\
				srcs/utils/collisions.c\
				srcs/drawing/draw_player.c\
				srcs/drawing/draw_map.c\
				srcs/menu/generate.c\
				srcs/menu/loop.c\
				srcs/menu/render.c\
				srcs/menu/utils.c\
				srcs/menu/mouse_hook.c\
				srcs/menu/dragbar.c\
				srcs/parsing/parsing.c

NAME		= cub3D
minilibx	= mlx/libmlx.a
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra
MLB_FLAGS	= -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm -lpthread

$(OBJS_DIR)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs/parsing
	@mkdir -p $(OBJS_DIR)srcs/mlx_utils
	@mkdir -p $(OBJS_DIR)srcs/raycasting
	@mkdir -p $(OBJS_DIR)srcs/utils
	@mkdir -p $(OBJS_DIR)srcs/drawing
	@mkdir -p $(OBJS_DIR)srcs/menu
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME_B)$(END)\n"

all: $(NAME)

bonus:	$(NAME_B)

maker:
	@make -C mlx

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_B)
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make clean -C mlx
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re
