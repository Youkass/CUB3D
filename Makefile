# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by youbougre         #+#    #+#              #
#    Updated: 2022/10/25 20:29:41 by dasereno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/main.c\
				srcs/shoot.c\
				srcs/ft_itoa.c\
				srcs/raycasting/raycasting_utils.c\
				srcs/raycasting/raycasting.c\
				srcs/raycasting/spritecasting.c\
				srcs/raycasting/player_casting.c\
				srcs/raycasting/name_casting.c\
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
				srcs/drawing/draw_text.c\
				srcs/menu/generate.c\
				srcs/menu/menu_lobby.c\
				srcs/menu/loop.c\
				srcs/menu/render.c\
				srcs/menu/utils.c\
				srcs/menu/mouse_hook.c\
				srcs/menu/dragbar.c\
				srcs/parsing/parsing.c\
				srcs/network_client/network_utils.c\
				srcs/network_client/client.c

SERVER_SRCS		= 	srcs/network/server.c\
					srcs/network/lobby.c\
				  	srcs/network_client/network_utils.c\
				  	srcs/network/server_thread.c\
					srcs/utils/clock.c\
					srcs/utils/math.c\
					srcs/parsing/parsing.c


NAME		= cub3D
SERVER		= server
minilibx	= mlx/libmlx.a
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/
OBJS_DIR_SERVER	= objs_server/
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
OBJS_SERVER		= $(SERVER_SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))
OBJECTS_PREFIXED_SERVER = $(addprefix $(OBJS_DIR_SERVER), $(OBJS_SERVER))
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra
MLB_FLAGS	= -g -fsanitize=address -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm -pthread


$(OBJS_DIR)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs/parsing
	@mkdir -p $(OBJS_DIR)srcs/mlx_utils
	@mkdir -p $(OBJS_DIR)srcs/raycasting
	@mkdir -p $(OBJS_DIR)srcs/utils
	@mkdir -p $(OBJS_DIR)srcs/drawing
	@mkdir -p $(OBJS_DIR)srcs/menu
	@mkdir -p $(OBJS_DIR)srcs/network_client
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(OBJS_DIR_SERVER)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR_SERVER)
	@mkdir -p $(OBJS_DIR_SERVER)srcs/network
	@mkdir -p $(OBJS_DIR_SERVER)srcs/parsing
	@mkdir -p $(OBJS_DIR_SERVER)srcs/utils
	@mkdir -p $(OBJS_DIR_SERVER)srcs/network_client
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME_B)$(END)\n"

$(SERVER): $(OBJECTS_PREFIXED_SERVER) maker
	@$(CC) -o $(SERVER) $(OBJECTS_PREFIXED_SERVER) $(CC_FLAGS) -pthread -Lincludes -lm
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"
all: $(NAME) $(SERVER)

bonus:	$(NAME_B)

maker:
	@make -C mlx

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_B)
	@rm -rf $(OBJS_DIR_SERVER)
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make clean -C mlx
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@rm -f $(SERVER)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re
