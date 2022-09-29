/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:30:30 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 17:08:45 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/time.h>

typedef struct	s_obj
{
	int		id;
	int		x;
	int		y;
	char	c;
}	t_obj;

typedef struct s_int
{
	int	i;
	int	j;
	int	x;
	int	y;
}	t_int;

typedef struct s_vector2D
{
	int	x;
	int	y;
}	t_vector2D;

typedef struct s_vector3D
{
	int	x;
	int	y;
	int	z;
}	t_vector3D;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_data
{	
	void	*img;
	char	*addr;
	char	**map;
	t_obj	**coord_map;
	int		map_width;
	int		map_height;
	int		scale;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_data;

typedef struct s_enum_key
{
	int	id;
	int	(*ft_hook_key)(void);
}	t_enum_key;

typedef struct s_enum_mouse
{
	int	id;
	int	(*ft_hook_mouse)(void);
}	t_enum_mouse;

typedef struct s_button
{
	int				state;
	struct timeval	clock;
	t_vector2D		hitbox[4];
}	t_button;

typedef struct s_menu
{
	t_data		**buttons;
	t_button	*s_state;
	t_button	*o_state;
	int			mute_s_state;
	int			mute_m_state;
	t_data		**bar;
	t_data		logo;
	t_data		bg;
	t_data		img;
	int			s_bar;
	int			m_bar;
	t_vector2D	pos_s_bar;
	int			draging_s;
	t_vector2D	pos_m_bar;
	int			draging_m;
	int			mode;
}	t_menu;

typedef struct s_key
{
	int	mouse;
	int	w;
	int	a;
	int	s;
	int	d;
	int	esc;
}	t_key;

typedef struct s_var
{
	t_menu		*menu;
	t_vector2D	m_pos;
	int			mode;
	t_key		key;
}	t_var;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

#endif
