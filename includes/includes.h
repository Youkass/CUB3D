/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:31:18 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/24 13:42:06 by yobougre         ###   ########.fr       */
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
# include <pthread.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include <sys/time.h>
# include <signal.h>

# define GAME 0
# define MENU 1
# define ONLINE_START 2
# define LOBBY_WAIT 3

# define MENU_START 0
# define MENU_OPTION 1
# define MENU_GAME 2
# define MENU_PLAYER 3
# define MENU_PSEUDO 4
# define MENU_LOBBY 5
# define MENU_IP 6

# define NB_WEAPONS 1

# define TH_RAY 5

# define A 97
# define B 98
# define C 99
# define D 100
# define E 101
# define F 102
# define G 103
# define H 104
# define I 105
# define J 106
# define K 107
# define L 108
# define M 109
# define N 110
# define O 111
# define P 112
# define Q 113
# define R 114
# define S 115
# define T 116
# define U 117
# define V 118
# define W 119
# define X 120
# define Y 121
# define Z 122


# define ZERO 48
# define ONE 49
# define TWO 50
# define THREE 51
# define FOUR 52
# define FIVE 53
# define SIX 54
# define SEVEN 55
# define EIGHT 56
# define NINE 57

# define _ 45

# define ERASE 65288
# define ENTER 65293

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
# define ARR_UP 65362
# define ARR_DOWN 65364
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define SPACE 32
# define WALL 1
# define PLAYER 2
# define VOID 3
# define MAP 4

# define MINIMAP_SIZE 512
# define MINIMAP_OFFSET (WIN_W - MINIMAP_SIZE)

#define uDiv 1
#define vDiv 1
#define vMove 0.0
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

# define OFFSET_Y 0
# define OFFSET_X 0
# define BUT_CL_TIME 100000

# define BAR_INC 2.04
# define BAR_MAX 204
# define BAR_H 27

# define NONE 0
# define CLIENT 1
# define SERVER 2

# define FAILURE 1
# define SUCCESS 0

# define TMP_FILE ".tmp"
# define CMD_PRINT_IP "hostname -i > .tmp"
//# define CMD_PRINT_IP "127.0.0.1"
//# define CMD_PRINT_IP "ipconfig getifaddr en0"
# define MAX_PLAYER 6
# define HOST 1
# define BUFFER_SIZE 30
#endif
