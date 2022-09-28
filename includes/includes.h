/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:31:18 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 14:10:14 by yobougre         ###   ########.fr       */
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
# define WALL 1
# define PLAYER 2
# define VOID 3
# define MAP 4

#endif
