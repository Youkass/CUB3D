/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:31:18 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/04 15:17:51 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
w : 119
a : 97
s : 115
d : 100
esc : 65307
+ : 61
- : 45

*/

#ifndef INCLUDES_H
# define INCLUDES_H

# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include <sys/time.h>

# define GAME 0
# define MENU 1


# define PI 3.14159 
# define P2 (PI/2)
# define P3 (3*PI/2)
# define DR 0.0174533
# define WIN_H 900
# define WIN_W 1440
# define PRG_NAME "Cub3d by Curly Squad"
# define MAX_KEYS 5
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define WALL 1
# define PLAYER 2
# define VOID 3
# define MAP 4

# define MINIMAP_SIZE 512
# define MINIMAP_OFFSET (WIN_W - MINIMAP_SIZE)

# define PLAY 0
# define OPTIONS 1
# define CREDITS 2
# define EXIT 3
# define RESTART 4
# define QUIT 5
# define MUTE_M 6
# define MUTE_S 7
# define MUSIC 8
# define SOUND 9
# define L_ARR 10
# define R_ARR 11

# define NORMAL 0
# define HOVER 1
# define ACTIVE 2

# define BAR_LEFT 2
# define BAR_MID 1
# define BAR_RIGHT 0

# define EMPTY 0
# define FILL 1 

# define MENU_START 0
# define MENU_OPTION 1
# define MENU_GAME 2

# define OFFSET_Y 0
# define OFFSET_X 0
# define BUT_CL_TIME 100000

# define BAR_INC 2.04
# define BAR_MAX 204
# define BAR_H 27

#endif
