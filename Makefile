# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by youbougre         #+#    #+#              #
#    Updated: 2022/11/15 18:01:06 by yobougre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/main.c\
				srcs/team.c\
				srcs/tools.c\
				srcs/shoot.c\
				srcs/ft_itoa.c\
				srcs/kill_log.c\
				srcs/raycasting/raycasting_utils.c\
				srcs/raycasting/raycasting.c\
				srcs/raycasting/spritecasting.c\
				srcs/raycasting/player_casting.c\
				srcs/raycasting/name_casting.c\
				srcs/raycasting/bullet_casting.c\
				srcs/mlx_utils/mlx_utils.c\
				srcs/mlx_utils/render.c\
				srcs/utils/singleton.c\
				srcs/utils/singleton_2.c\
				srcs/utils/malloc_hooks_enum.c\
				srcs/utils/key_hooks.c\
				srcs/utils/clock.c\
				srcs/utils/garbage.c\
				srcs/utils/list.c\
				srcs/utils/collisions.c\
				srcs/utils/sound.c\
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
				srcs/menu/recv_utils.c\
				srcs/parsing/parsing.c\
				srcs/network_client/network_utils.c\
				srcs/network_client/client.c\
				srcs/math/math.c\
				srcs/math/vector/operator2D.c\
				srcs/math/vector/operator2F.c\
				srcs/math/vector/tools.c\
				srcs/init.c\
				miniaudio/extras/miniaudio_split/miniaudio.c\
				srcs/new_raycaster.c\
				srcs/dyn_array.c

SERVER_SRCS		= 	srcs/network/server.c\
					srcs/network/lobby.c\
					srcs/kill_log.c\
				  	srcs/network_client/network_utils.c\
				  	srcs/network/server_thread.c\
					srcs/math/math.c\
					srcs/math/vector/operator2D.c\
					srcs/math/vector/operator2F.c\
					srcs/math/vector/tools.c\
					srcs/utils/singleton.c\
					srcs/utils/singleton_2.c\
					srcs/utils/malloc_hooks_enum.c\
					srcs/utils/key_hooks.c\
					srcs/utils/clock.c\
					srcs/utils/list.c\
					srcs/utils/collisions.c\
					srcs/utils/garbage.c\
					srcs/tools.c\
					srcs/shoot.c\
					srcs/dyn_array.c\
					srcs/init.c\
					srcs/menu/recv_utils.c\
					srcs/parsing/parsing.c\
					srcs/team.c\


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
MLB_FLAGS	= -O3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm -pthread -ldl -lpthread


$(OBJS_DIR)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs/parsing
	@mkdir -p $(OBJS_DIR)srcs/mlx_utils
	@mkdir -p $(OBJS_DIR)srcs/raycasting
	@mkdir -p $(OBJS_DIR)srcs/utils
	@mkdir -p $(OBJS_DIR)srcs/drawing
	@mkdir -p $(OBJS_DIR)srcs/menu
	@mkdir -p $(OBJS_DIR)srcs/math
	@mkdir -p $(OBJS_DIR)srcs/math/vector
	@mkdir -p $(OBJS_DIR)srcs/network_client
	@mkdir -p $(OBJS_DIR)miniaudio/extras/miniaudio_split/
	@mkdir -p $(OBJS_DIR)srcs
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(OBJS_DIR_SERVER)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR_SERVER)
	@mkdir -p $(OBJS_DIR_SERVER)srcs/math
	@mkdir -p $(OBJS_DIR_SERVER)srcs/menu
	@mkdir -p $(OBJS_DIR_SERVER)srcs/math/vector
	@mkdir -p $(OBJS_DIR_SERVER)srcs/network
	@mkdir -p $(OBJS_DIR_SERVER)srcs/parsing
	@mkdir -p $(OBJS_DIR_SERVER)srcs/utils
	@mkdir -p $(OBJS_DIR_SERVER)srcs/network_client
	@mkdir -p $(OBJS_DIR_SERVER)srcs
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME_B)$(END)\n"

$(SERVER): $(OBJECTS_PREFIXED_SERVER) maker
	@$(CC) -o $(SERVER) $(OBJECTS_PREFIXED_SERVER) $(CC_FLAGS) -O3 -pthread -Lincludes -lm
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME) server

server: $(SERVER)

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
	@make clean -C miniaudio 
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@rm -f $(SERVER)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re
