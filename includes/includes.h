/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:31:18 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 17:36:22 by denissereno      ###   ########.fr       */
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

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"
//# include "../libft/libft.h"

# define PI 3.14159 
# define P2 PI/2
# define P3 3*PI/2
# define WIN_H 1080
# define WIN_W 1920
# define PRG_NAME "Cub3d by Curly Squad"
# define MAX_KEYS 5
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

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

#endif
