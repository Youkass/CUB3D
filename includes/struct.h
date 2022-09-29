/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:30:30 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 13:01:42 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUC_H
# define STRUC_H

# define GAME 0
# define MENU 1

typedef struct s_int
{
	int	i;
	int	j;
	int	x;
	int	y;
}	t_int;

typedef struct s_vector2D
{
    int x;
    int y;
}   t_vector2D;

typedef struct s_vector3D
{
    int x;
    int y;
    int z;
}   t_vector3D;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct	s_data
{	
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}	t_data;

typedef struct	s_enum_key
{
	int	id;
	int	(*ft_hook_key)(void);
}	t_enum_key;

typedef struct	s_enum_mouse
{
	int	id;
	int	(*ft_hook_mouse)(void);
}	t_enum_mouse;

typedef	struct	s_button
{
	int	state;
	t_vector2D hitbox[4];
}	t_button;

typedef struct  s_menu
{
    t_data  	**buttons;
	t_button	*s_state;
	t_button	*o_state;
    t_data  	**bar;
	t_data		logo;
	t_data		bg;
	t_data		img;
	int			mode;
}   t_menu;

typedef struct  s_var
{
    t_menu  	*menu;
	t_vector2D	m_pos;
	int			mode;
}   t_var;

typedef struct	s_player
{
	int	x;
	int	y;
}	t_player;

#endif
