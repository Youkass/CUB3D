/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:30:30 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/05 23:26:46 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/time.h>
# include <pthread.h>
# include "includes.h"

struct s_data;

typedef struct s_vector2F
{
	float	x;
	float	y;
}	t_vector2F;

typedef struct s_vector2FD
{
	double	x;
	double	y;
}	t_vector2FD;

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

typedef struct	s_circle
{
	float	x;
	float	y;
	float	radius;
}	t_circle;

typedef struct	s_hitbox
{
	t_circle	hit;
	t_vector2D	nb[8];
	int			n;
}	t_hitbox;

typedef struct s_int
{
	int	i;
	int	j;
	int	x;
	int	y;
}	t_int;

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
	int		map_width;
	int		map_height;
	int		scale;
	int		half_scale;
	int		half_scale_offset;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_data;

typedef struct	s_obj
{
	int			id;
	float		x;
	float		y;
	char		c;
	float		dx;
	float		dy;
	float		old_dx;
	float		old_dy;
	float		angle;
	double		move_speed;
	double		rot_speed;
	t_vector2F	plane;
	t_vector2F	old_plane;
	t_hitbox	hb;
	t_data		sprite;
}	t_obj;

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

typedef struct s_raycasting
{
	t_vector2D		step;
	t_vector2D		map;
	t_vector2FD		cam;
	t_vector2FD		dir;
	t_vector2FD		side_dist;
	t_vector2FD		delta;
	int				hit;
	int				x;
	int				y;
	int				side;
	int				line_h;
	int				draw_start;
	double			wall_x;
	double			tex_step;
	t_vector2D		tex;
	double			tex_pos;
	int				draw_end;
	int				color;
	double			perp_wall_dist;
	int				max_y;
	int				min_y;
	t_obj			pl;
}	t_raycasting;

typedef struct s_spritecasting
{
	int			nb_sprites;
	int			*sprite_order;
	int			*sprite_dist;
	t_vector2FD	pos;
	double		inv_det;
	t_vector2FD	trans;
	int			sprite_screen_x;
	t_vector2D	size;
	t_vector2D	draw_start;
	t_vector2D	draw_end;
	int			stripe;
	int			i;
	t_vector2D	tex;
	int			d;
	int			color;
}	t_spritecasting;

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
	t_data		wall;
}	t_menu;

typedef struct	s_rect
{
	float	width;
	float	height;
	float	x;
	float	y;
}	t_rect;

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
	t_menu			*menu;
	t_vector2D		m_pos;
	int				mode;
	t_key			key;
	struct timeval	clock;
	unsigned long	time;
	unsigned long	old_time;
	double			frame_time;
	pthread_t		th[TH_RAY];
	pthread_t		th_void[10];
	t_obj			**coord_map;
	t_obj			player2;
	int				zbuffer[WIN_W];
}	t_var;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct	s_nb
{
	int			i;
	int			ret;
	t_vector2F	nearest[2];
	t_vector2F	potential;
}	t_nb;

#endif
