/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:30:30 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/20 00:01:10 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/time.h>
# include <pthread.h>
# include "includes.h"

struct s_obj;
typedef struct s_obj t_obj;

struct	s_server_data;
typedef struct	s_server_data t_server_data;

typedef struct	s_media
{
	ma_result			result;
	ma_decoder			decoder;
	ma_device_config	device_config;
	ma_device			device;
	ma_engine			engine;
	ma_sound			sound[NB_SOUND][5];
	ma_sound			shot_sound[MAX_SHOT_SOUND];
	ma_sound_config		sound_config[NB_SOUND];
}	t_media;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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

typedef struct s_vector3F
{
	float	x;
	float	y;
	float	z;
}	t_vector3F;

typedef struct	s_circle
{
	t_vector2F	pos;
	float		r;
}	t_circle;

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
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					h;
	int					w;
	t_vector2D			pos;
}	t_data;


typedef struct	s_hit
{
	int		shoot;
	int		id;
}	t_hit;

typedef struct	s_weapon
{
	int		id;
	char	*name;
	int		power;
	unsigned long		reload_ms;
	int		full_ammo;
	int		ammo;
	int		range;
	int		headshot;
	int		footshot;
	int		shot_frames;
	int		reload_frames;
	int		anim_shotms;
	int		anim_reloadms;
}	t_weapon;

typedef struct	s_hitbox
{
	t_circle	hit;
	t_vector2D	nb[8];
	int			n;
}	t_hitbox;

typedef struct	s_velo
{
	t_vector2F	dist;
	t_vector2F	velo;
	int			time_ms;
}	t_velo;

typedef struct	s_velo3
{
	t_vector3F	dist;
	t_vector3F	velo;
	int			time_ms;
}	t_velo3;

typedef struct	s_elem
{
	int				ids[2];
	unsigned long	start;
}	t_elem;

typedef struct	s_log
{
	t_list			*log;
	pthread_mutex_t	mutex;
}	t_log;


/*
 Le but de cette struct est d'en faire une liste chainée pour pouvoir display
 toutes les bullets en temps réel. On divise le segment en 6 point et on pourra
 display du point 2 au point 5 (1 et 6 étant le debut et la fin du tir on
 ne les affiche donc pas).
 N sera la ou on en est (0-> premier display, 4-> dernier display).
 Start et end pos sont la position de depart et de fin.
 pos est la position actuel.
 start_time est le moment de la clock ou le shot a demarré (peut etre inutile
 car je ferai surement le display en fonction du framerate)
 weapon_type est l'arme avec laquelle on a tiré (cela peut peut etre changer
 la maniere d'afficher).
*/

typedef struct	s_shot
{
	t_velo3			velo;
	t_vector3F		start_pos;
	t_vector3F		end_pos;
	t_vector3F		pos;

	unsigned long	start_time;
	int				n;
	int				weapon_type;
	int				shot;
}	t_shot;


typedef struct	s_array
{
	int		*array;
	size_t	n;
	size_t	size;
} t_array;


struct	s_obj
{
	int			id;
	int			team_id;
	int			team;
	float		x;
	float		y;
	float		z;
	char		c;
	float		dx;
	float		dy;
	float		da;
	float		old_dx;
	float		old_dy;
	float		angle;
	double		move_speed;
	double		rot_speed;
	int			is_walking;
	int			is_dead;
	unsigned long	start_dead;
	unsigned long	start_reload;
	int			can_shoot;
	int			death_n;
	int			death_start;
	int			weapon_id;
	int			health;
	int			ammo[NB_WEAPONS];
	int			full_ammo[NB_WEAPONS];
	char		pseudo[16];
	t_vector2F	plane;
	t_vector2F	old_plane;
	t_hitbox	hb;
	int			pitch;
	int			norm_pitch;
	t_shot		shott[MAX_BULLET];
	int			shoot_n;
	t_hit		shooted;
	int			exchange;
	int			is_shooting;
	int			is_start;
	int			change_team;
	float		 scale;
	int			money;
	int			spectate;
	int			spec_id;
	int			kills;
	int			deaths;
	int			is_crouching;
	int			kill_round[9];
	int			kill_match[120];
	int			nr;
	int			nm;
	int			kevlar; // entre 0 et 2. 0 = pas de Kevlar, 1 = Kevlar, 2 = Kevlar + casque
	int			touched;
	int			hitted;
};

typedef struct	s_network_data
{
	t_obj				player;
	int					socket;
	int					is_host;
}	t_network_data;
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
	int			move_screen;
}	t_spritecasting;

typedef struct s_menu
{
	t_data		**buttons;
	t_button	*s_state;
	t_button	*o_state;
	t_button	*p_state;
	int			mute_s_state;
	int			mute_m_state;
	t_data		**bar;
	t_data		logo;
	t_data		bg;
	t_data		img;
	t_data		nb_p[4][3];
	int			s_bar;
	int			m_bar;
	t_vector2D	pos_s_bar;
	int			draging_s;
	t_vector2D	pos_m_bar;
	t_vector2D	double_pos[2];
	int			draging_m;
	int			mode;
	t_data		wall;
	t_data		planets[2];
	t_vector2D	planets_pos[2];
	int			n;
	int			ny;
	unsigned long	start;
	t_data		wait;
	t_vector2D	draw_pl[2];
	int			n_ip;
}	t_menu;

typedef struct	s_rect
{
	float	w;
	float	h;
	float	x;
	float	y;
}	t_rect;

typedef enum s_key
{
	mouse = 0,
	a = 1,
	b = 2,
	c = 3,
	d = 4,
	e = 5,
	f = 6,
	g = 7,
	h = 8,
	i = 9,
	j = 10,
	k = 11,
	l = 12,
	m = 13,
	n = 14,
	o = 15,
	p = 16,
	q = 17,
	r = 18,
	s = 19,
	t = 20,
	u = 21,
	v = 22,
	w = 23,
	x = 24,
	y = 25,
	z = 26,
	zero = 27,
	one = 28,
	two = 29,
	three = 30,
	four = 31,
	five = 32,
	six = 33,
	seven = 34,
	eight = 35,
	nine = 36,
	underscore = 37,
	esc = 38,
	up = 39,
	down = 40,
	left = 41,
	right = 42,
	space = 43,
	ctrl = 44,
	maj = 45
}	t_key;

typedef struct s_var
{
	t_menu				*menu;
	t_vector2D			m_pos;
	int					mode;
	struct timeval		clock;
	unsigned long		time;
	unsigned long		old_time;
	double				frame_time;
	pthread_t			th[TH_RAY];
	pthread_t			th_void[10];
	t_obj				**coord_map;
	t_obj				player2;
	int					zbuffer[WIN_W];
	unsigned long		walk_start;
	int					walk_n;
	t_obj				o_player[MAX_PLAYER];
	t_obj				sort_player[MAX_PLAYER];
	t_weapon			weapon[NB_WEAPONS];
	int					linked_players;
	char				ip[16];
	int					started;
	int					is_host;
	struct sockaddr_in	client;
	int					nb_player;
	int					socket;
	char				**before_map;
	char				map[1024][1024];
	int					map_width;
	int					map_height;
	int					scale;
	int					half_scale;
	int					half_scale_offset;
	unsigned int		start_click;
	int					click_keycode;
	int					click;
	int					key[46];
	int					red[5];
	int					blue[5];
	int					neutral[MAX_PLAYER];
	int					n_red;
	int					n_neutral;
	int					n_blue;
	int					team_start;
	int					team_match;
	int					freeze;
	int					round_state;
	int					last_round_winner;
	int					match_finished;
	int					player_alive;
	int					red_alive;
	int					blue_alive;
	int					ran_i;
	int					alive[2];
	t_log				*log;
	int					restart;
	unsigned long		shotanim_start;
	int					shot_anim;
	unsigned long		reloadanim_start;
	int					reload_anim;
	int					pid;
	unsigned long		start_touch;
	unsigned long		start_hit;
	int					time_start;
	unsigned char		colors[2][4];
}	t_var;

typedef struct	s_image
{
	t_data			alpha[255];
	t_data			rifle;
	t_data			pseudo_img[MAX_PLAYER];
	t_data			bullet;
	t_data			bg;
	t_data			dsprite[16];
	t_data			dsprite_red[16];
	t_data			sprite;
	t_data			death_sprite;
	t_data			death_sprite_red;
	t_data			walk_sprite[8];
	t_data			walk_sprite_red[8];
	t_data			intro_sprite[8];
	t_data			crosshair;
	t_data			hitmarker;
	t_data			front;
	t_data			ammo;
	t_data			*weapons[3][3];
	t_data			dir[4];
}	t_image;

typedef struct	s_team
{
	int			win;
	int			loose;
	int			players[5];
	int			deaths;
	t_vector2F	team_spawn;
	t_vector2F	player_spawn[5];
}	t_team;

typedef struct	s_player_stat
{
	int	dead;
	int	kills;
	int	deaths;
	int	id;
}	t_player_stat;

/*
Round_state : 0 : Rien. 1 = Gagne. 2 : Perd*/
typedef struct	s_team_serv
{
	int				wins;
	int				looses;
	int				round_state;
	t_player_stat	players[5];
}	t_team_serv;

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

typedef struct	s_data_plyr
{
	t_obj	player_data[MAX_PLAYER];
	int		nb_linked;
	int		nb_player;
}	t_data_plyr;

typedef struct	s_send_client
{
	t_obj		player;
	int			start;
	int			flag;
}	t_send_client;

typedef struct	s_send_client_game
{
	t_obj		player;
	int			red_wins;
	int			blue_wins;
	int			round_end;
	int			restart;
}	t_send_client_game;

typedef struct	s_send_server
{
	t_obj		player[MAX_PLAYER];
	int			start;
	int			flag;
	int			linked_pl;
}	t_send_server;

typedef struct	s_send_server_game
{
	t_obj		player[MAX_PLAYER];
	int			linked_players;
	int			match_finished;
	int			round_winner;
	int			round_state;
	int			player_alive;
	int			red_alive;
	int			blue_alive;
	int			restart;
	int			time;
}	t_send_server_game;

typedef struct	s_client_thread
{
	pthread_mutex_t			*mutex;
	pthread_mutex_t			*mutex_linked;
	pthread_mutex_t			*mutex_start;
	struct sockaddr_in		sockclient;
	pthread_t				thread_id;
	t_obj					player_data;
	socklen_t				csize;
	int						id;
	int						nb_players;
	int						socket;
	int						is_recv;
	int						is_send;
	int						start;
	int						blue;
	int						red;
	struct s_server_data	*serv;
	int						team_id;
	int						team;
	int						restart;
	int						round_state_send[N_RSTATE];
}	t_client_thread;

struct	s_server_data
{
	struct sockaddr_in		server;
	t_client_thread			clients[MAX_PLAYER];
	t_array					teams[2];
	pthread_mutex_t			mutex;
	pthread_mutex_t			mutex_start;
	pthread_mutex_t			mutex_linked;
	t_obj					player_data[MAX_PLAYER];
	t_data_plyr				players;
	socklen_t				csize;
	int						socket;
	int						nb_players;
	int						linked_players;
	int						started;
	int						nb_red;
	int						nb_blue;
	t_team_serv				team_data[2];
	struct timeval			clock;
	unsigned long			start;
	int						round_state[N_RSTATE];
	int						clock_started;
	int						match_finished;
	int						player_alive;
	int						red_alive;
	int						blue_alive;
	int						round_end;
	int						restart;
	char					map[1024][1024];
	int						map_width;
	int						map_height;
};

typedef struct	s_intro
{
	t_vector2D		double_pos[2];
	unsigned long	check;
	int				limite;
}	t_intro;

#endif
