# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by youbougre         #+#    #+#              #
#    Updated: 2022/12/05 19:55:49 by dasereno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS_B		=	srcs_bonus/main.c\
				srcs_bonus/main_utils.c\
				srcs_bonus/team.c\
				srcs_bonus/tools.c\
				srcs_bonus/shoot/shoot.c\
				srcs_bonus/shoot/shoot_utils.c\
				srcs_bonus/shoot/shoot_utils_2.c\
				srcs_bonus/shoot/shoot_wall.c\
				srcs_bonus/ft_itoa.c\
				srcs_bonus/kill_log.c\
				srcs_bonus/raycasting/raycasting_utils.c\
				srcs_bonus/raycasting/raycasting.c\
				srcs_bonus/raycasting/raycasting_2.c\
				srcs_bonus/raycasting/player_casting.c\
				srcs_bonus/raycasting/player_casting_2.c\
				srcs_bonus/raycasting/player_casting_3.c\
				srcs_bonus/raycasting/name_casting.c\
				srcs_bonus/raycasting/bullet_casting.c\
				srcs_bonus/mlx_utils/mlx_utils.c\
				srcs_bonus/mlx_utils/mlx_utils_2.c\
				srcs_bonus/mlx_utils/mlx_utils_3.c\
				srcs_bonus/mlx_utils/render.c\
				srcs_bonus/utils/singletons/singleton.c\
				srcs_bonus/utils/singletons/singleton_2.c\
				srcs_bonus/utils/singletons/singleton_3.c\
				srcs_bonus/utils/restart.c\
				srcs_bonus/utils/malloc_hooks_enum.c\
				srcs_bonus/utils/hooks/key_hooks.c\
				srcs_bonus/utils/hooks/key_hooks_2.c\
				srcs_bonus/utils/hooks/movements.c\
				srcs_bonus/utils/hooks/movements_2.c\
				srcs_bonus/utils/hooks/escape.c\
				srcs_bonus/utils/clock.c\
				srcs_bonus/utils/garbage/garbage.c\
				srcs_bonus/utils/garbage/garbage_2.c\
				srcs_bonus/utils/garbage/garbage_3.c\
				srcs_bonus/utils/list.c\
				srcs_bonus/utils/collisions/collisions.c\
				srcs_bonus/utils/collisions/collisions_2.c\
				srcs_bonus/utils/collisions/collisions_3.c\
				srcs_bonus/utils/sounds/sound.c\
				srcs_bonus/utils/sounds/sound_2.c\
				srcs_bonus/utils/sounds/sound_3.c\
				srcs_bonus/utils/sounds/sound_4.c\
				srcs_bonus/drawing/draw_player.c\
				srcs_bonus/drawing/draw_player_2.c\
				srcs_bonus/drawing/draw_map.c\
				srcs_bonus/drawing/draw_map_2.c\
				srcs_bonus/drawing/draw_map_3.c\
				srcs_bonus/drawing/draw_text.c\
				srcs_bonus/drawing/draw_text_2.c\
				srcs_bonus/menu/generate.c\
				srcs_bonus/menu/generate_2.c\
				srcs_bonus/menu/generate_3.c\
				srcs_bonus/menu/generate_4.c\
				srcs_bonus/menu/menu_lobby.c\
				srcs_bonus/menu/loop.c\
				srcs_bonus/menu/loop_2.c\
				srcs_bonus/menu/loop_3.c\
				srcs_bonus/menu/loop_4.c\
				srcs_bonus/menu/render.c\
				srcs_bonus/menu/render_2.c\
				srcs_bonus/menu/render_3.c\
				srcs_bonus/menu/render_4.c\
				srcs_bonus/menu/utils.c\
				srcs_bonus/menu/utils_2.c\
				srcs_bonus/menu/utils_3.c\
				srcs_bonus/menu/mouse_hook.c\
				srcs_bonus/menu/intro.c\
				srcs_bonus/menu/intro_2.c\
				srcs_bonus/menu/dragbar.c\
				srcs_bonus/menu/recv_utils.c\
				srcs_bonus/parsing/parsing.c\
				srcs_bonus/parsing/parsing_2.c\
				srcs_bonus/parsing/parsing_3.c\
				srcs_bonus/parsing/parsing_4.c\
				srcs_bonus/parsing/args.c\
				srcs_bonus/parsing/args_2.c\
				srcs_bonus/parsing/args_3.c\
				srcs_bonus/network_client/network_utils.c\
				srcs_bonus/network_client/client.c\
				srcs_bonus/network_client/client_2.c\
				srcs_bonus/network_client/client_3.c\
				srcs_bonus/network_client/client_4.c\
				srcs_bonus/math/math.c\
				srcs_bonus/math/math_2.c\
				srcs_bonus/math/vector/operator2D.c\
				srcs_bonus/math/vector/operator2F.c\
				srcs_bonus/math/vector/tools.c\
				srcs_bonus/math/vector/tools_2.c\
				srcs_bonus/mlx_utils/hud.c\
				srcs_bonus/mlx_utils/sky.c\
				srcs_bonus/mlx_utils/sky_2.c\
				srcs_bonus/init/init.c\
				srcs_bonus/init/init_2.c\
				srcs_bonus/init/init_3.c\
				srcs_bonus/init/init_4.c\
				srcs_bonus/mouse.c\
				srcs_bonus/key.c\
				srcs_bonus/loop_hook.c\
				srcs_bonus/clock_2.c\
				srcs_bonus/dyn_array_2.c\
				miniaudio/extras/miniaudio_split/miniaudio.c\
				srcs_bonus/utils/click.c\
				srcs_bonus/dyn_array.c

SERVER_SRCS		= 	srcs_bonus/network/server.c\
					srcs_bonus/network/lobby.c\
					srcs_bonus/network/lobby_2.c\
				  	srcs_bonus/network/server_thread.c\
					srcs_bonus/network/round_1.c\
					srcs_bonus/network/round_2.c\
					srcs_bonus/network/send.c\
					srcs_bonus/network/init.c\
					srcs_bonus/network/recv.c\
					srcs_bonus/main_utils.c\
					srcs_bonus/team.c\
					srcs_bonus/tools.c\
					srcs_bonus/shoot/shoot.c\
					srcs_bonus/shoot/shoot_utils.c\
					srcs_bonus/shoot/shoot_utils_2.c\
					srcs_bonus/shoot/shoot_wall.c\
					srcs_bonus/ft_itoa.c\
					srcs_bonus/kill_log.c\
					srcs_bonus/raycasting/raycasting_utils.c\
					srcs_bonus/raycasting/raycasting.c\
					srcs_bonus/raycasting/raycasting_2.c\
					srcs_bonus/raycasting/player_casting.c\
					srcs_bonus/raycasting/player_casting_2.c\
					srcs_bonus/raycasting/player_casting_3.c\
					srcs_bonus/raycasting/name_casting.c\
					srcs_bonus/raycasting/bullet_casting.c\
					srcs_bonus/mlx_utils/mlx_utils.c\
					srcs_bonus/mlx_utils/mlx_utils_2.c\
					srcs_bonus/mlx_utils/mlx_utils_3.c\
					srcs_bonus/mlx_utils/render.c\
					srcs_bonus/utils/singletons/singleton.c\
					srcs_bonus/utils/singletons/singleton_2.c\
					srcs_bonus/utils/singletons/singleton_3.c\
					srcs_bonus/utils/restart.c\
					srcs_bonus/utils/malloc_hooks_enum.c\
					srcs_bonus/utils/hooks/key_hooks.c\
					srcs_bonus/utils/hooks/key_hooks_2.c\
					srcs_bonus/utils/hooks/movements.c\
					srcs_bonus/utils/hooks/movements_2.c\
					srcs_bonus/utils/hooks/escape.c\
					srcs_bonus/utils/clock.c\
					srcs_bonus/utils/garbage/garbage.c\
					srcs_bonus/utils/garbage/garbage_2.c\
					srcs_bonus/utils/garbage/garbage_3.c\
					srcs_bonus/utils/list.c\
					srcs_bonus/utils/collisions/collisions.c\
					srcs_bonus/utils/collisions/collisions_2.c\
					srcs_bonus/utils/collisions/collisions_3.c\
					srcs_bonus/utils/sounds/sound.c\
					srcs_bonus/utils/sounds/sound_2.c\
					srcs_bonus/utils/sounds/sound_3.c\
					srcs_bonus/utils/sounds/sound_4.c\
					srcs_bonus/drawing/draw_player.c\
					srcs_bonus/drawing/draw_player_2.c\
					srcs_bonus/drawing/draw_map.c\
					srcs_bonus/drawing/draw_map_2.c\
					srcs_bonus/drawing/draw_map_3.c\
					srcs_bonus/drawing/draw_text.c\
					srcs_bonus/drawing/draw_text_2.c\
					srcs_bonus/menu/generate.c\
					srcs_bonus/menu/generate_2.c\
					srcs_bonus/menu/generate_3.c\
					srcs_bonus/menu/generate_4.c\
					srcs_bonus/menu/menu_lobby.c\
					srcs_bonus/menu/loop.c\
					srcs_bonus/menu/loop_2.c\
					srcs_bonus/menu/loop_3.c\
					srcs_bonus/menu/loop_4.c\
					srcs_bonus/menu/render.c\
					srcs_bonus/menu/render_2.c\
					srcs_bonus/menu/render_3.c\
					srcs_bonus/menu/render_4.c\
					srcs_bonus/menu/utils.c\
					srcs_bonus/menu/utils_2.c\
					srcs_bonus/menu/utils_3.c\
					srcs_bonus/menu/mouse_hook.c\
					srcs_bonus/menu/intro.c\
					srcs_bonus/menu/intro_2.c\
					srcs_bonus/menu/dragbar.c\
					srcs_bonus/menu/recv_utils.c\
					srcs_bonus/parsing/parsing.c\
					srcs_bonus/parsing/parsing_2.c\
					srcs_bonus/parsing/parsing_3.c\
					srcs_bonus/parsing/parsing_4.c\
					srcs_bonus/parsing/args.c\
					srcs_bonus/parsing/args_2.c\
					srcs_bonus/parsing/args_3.c\
					srcs_bonus/network_client/network_utils.c\
					srcs_bonus/network_client/client.c\
					srcs_bonus/network_client/client_2.c\
					srcs_bonus/network_client/client_3.c\
					srcs_bonus/network_client/client_4.c\
					srcs_bonus/math/math.c\
					srcs_bonus/math/math_2.c\
					srcs_bonus/math/vector/operator2D.c\
					srcs_bonus/math/vector/operator2F.c\
					srcs_bonus/math/vector/tools.c\
					srcs_bonus/math/vector/tools_2.c\
					srcs_bonus/mlx_utils/hud.c\
					srcs_bonus/mlx_utils/sky.c\
					srcs_bonus/mlx_utils/sky_2.c\
					srcs_bonus/init/init.c\
					srcs_bonus/init/init_2.c\
					srcs_bonus/init/init_3.c\
					srcs_bonus/init/init_4.c\
					srcs_bonus/mouse.c\
					srcs_bonus/key.c\
					srcs_bonus/loop_hook.c\
					srcs_bonus/clock_2.c\
					srcs_bonus/dyn_array_2.c\
					miniaudio/extras/miniaudio_split/miniaudio.c\
					srcs_bonus/utils/click.c\
					srcs_bonus/dyn_array.c

SRCS		=	srcs/main.c\
				srcs/raycasting/raycasting_utils.c\
				srcs/raycasting/raycasting.c\
				srcs/mlx_utils/mlx_utils.c\
				srcs/utils/singleton.c\
				srcs/utils/key_hooks.c\
				srcs/utils/clock.c\
				srcs/utils/math.c\
				srcs/utils/garbage.c\
				srcs/utils/utils.c\
				srcs/utils/utils_2.c\
				srcs/utils/utils_3.c\
				srcs/utils/movements.c\
				srcs/parsing/parsing.c\
				srcs/parsing/parsing_2.c\
				srcs/parsing/split.c\
				srcs/parsing/args.c\
				srcs/parsing/args_2.c

NAME		= cub3D
NAME_B		= cub3D_bonus
SERVER		= server
minilibx	= mlx/libmlx.a
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/
OBJS_DIR_SERVER	= objs_server/
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
OBJS_AUDIO		= $(SRCS_B:.c=.o)
OBJS_SERVER		= $(SERVER_SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))
OBJECTS_PREFIXED_SERVER = $(addprefix $(OBJS_DIR_SERVER), $(OBJS_SERVER))
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra -g3
MLB_FLAGS	= -O3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm -pthread -ldl -lpthread -lXfixes

$(OBJS_DIR)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs/parsing
	@mkdir -p $(OBJS_DIR)srcs/mlx_utils
	@mkdir -p $(OBJS_DIR)srcs/raycasting
	@mkdir -p $(OBJS_DIR)srcs/utils
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(OBJS_DIR_B)%.o : %.c includes_bonus/cub.h
	@mkdir -p $(OBJS_DIR_B)
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/parsing
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/shoot
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/mlx_utils
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/raycasting
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/utils
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/init
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/utils/singletons
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/utils/collisions
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/utils/sounds
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/utils/garbage
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/utils/hooks
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/drawing
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/menu
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/math
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/math/vector
	@mkdir -p $(OBJS_DIR_B)srcs_bonus/network_client
	@mkdir -p $(OBJS_DIR_B)miniaudio/extras/miniaudio_split/
	@mkdir -p $(OBJS_DIR_B)srcs_bonus
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME_B)]${RST} '$<' $(END)"

$(OBJS_DIR_SERVER)%.o : %.c includes/cub.h
	@mkdir -p $(OBJS_DIR_SERVER)
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/raycasting
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/utils/hooks
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/mlx_utils
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/math
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/drawing
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/shoot
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/menu
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/init
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/math/vector
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/network
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/parsing
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/utils
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/utils/singletons
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/utils/collisions
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/utils/garbage
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/utils/sounds
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus/network_client
	@mkdir -p $(OBJS_DIR_SERVER)miniaudio/extras/miniaudio_split/
	@mkdir -p $(OBJS_DIR_SERVER)srcs_bonus
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME_B)$(END)\n"

$(SERVER): $(OBJECTS_PREFIXED_SERVER) maker
	@$(CC) -o $(SERVER) $(OBJECTS_PREFIXED_SERVER) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(SERVER)$(END)\n"


all: $(NAME) 

server: $(SERVER)


bonus:	$(NAME_B) $(SERVER)

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

.PHONY:		all clean fclean re server bonus
