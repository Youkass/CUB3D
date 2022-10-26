/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:32:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/26 18:42:22 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h> 

void	get_key(int keycode)
{
	if (keycode == A)
		_var()->key.a = 1;
	if (keycode == W)
		_var()->key.w = 1;
	if (keycode == S)
		_var()->key.s = 1;
	if (keycode == D)
		_var()->key.d = 1;
	if (keycode == ESC)
		_var()->key.esc = 1;
	if (keycode == ARR_UP)
		_var()->key.up = 1;
	if (keycode == ARR_DOWN)
		_var()->key.down = 1;
	if (keycode == ARR_LEFT)
		_var()->key.left = 1;
	if (keycode == ARR_RIGHT)
		_var()->key.right = 1;
	if (keycode == SPACE)
		_var()->key.space = 1;
}

int	ft_release(int keycode)
{
	if (keycode == A)
		_var()->key.a = 0;
	if (keycode == W)
	{
		_var()->key.w = 0;
		_player()->is_walking = 0;
	}
	if (keycode == S)
	{
		_var()->key.s = 0;
		_player()->is_walking = 0;
	}
	if (keycode == D)
		_var()->key.d = 0;
	if (keycode == ESC)
		_var()->key.esc = 0;
	if (keycode == ARR_UP)
		_var()->key.up = 0;
	if (keycode == ARR_DOWN)
		_var()->key.down = 0;
	if (keycode == ARR_LEFT)
		_var()->key.left = 0;
	if (keycode == ARR_RIGHT)
		_var()->key.right = 0;
	if (keycode == SPACE)
		_var()->key.space = 0;
	return (0);
}

void	generate_dsprite(void)
{
	_player()->dsprite[0] = generate_image("./img/soldier/front.xpm"); // front
	_player()->dsprite[1] = generate_image("./img/soldier/front_east_1.xpm"); // front east
	_player()->dsprite[2] = generate_image("./img/soldier/front_east_2.xpm"); // front east
	_player()->dsprite[3] = generate_image("./img/soldier/front_east_3.xpm"); // front east
	_player()->dsprite[4] = generate_image("./img/soldier/east.xpm"); // east
	_player()->dsprite[5] = generate_image("./img/soldier/back_east_1.xpm"); // back east
	_player()->dsprite[6] = generate_image("./img/soldier/back_east_2.xpm"); // back east
	_player()->dsprite[7] = generate_image("./img/soldier/back_east_3.xpm"); // back east
	_player()->dsprite[8] = generate_image("./img/soldier/back.xpm"); // back
	_player()->dsprite[9] = generate_image("./img/soldier/back_west_3.xpm"); // back west
	_player()->dsprite[10] = generate_image("./img/soldier/back_west_2.xpm"); // back west
	_player()->dsprite[11] = generate_image("./img/soldier/back_west_1.xpm"); // back west
	_player()->dsprite[12] = generate_image("./img/soldier/west.xpm"); // west
	_player()->dsprite[13] = generate_image("./img/soldier/front_west_3.xpm"); // front west
	_player()->dsprite[14] = generate_image("./img/soldier/front_west_2.xpm"); // front west
	_player()->dsprite[15] = generate_image("./img/soldier/front_west_1.xpm"); // front westwest

	_player()->walk_sprite[0] = generate_image("./img/soldier/walk/front.xpm");
	_player()->walk_sprite[1] = generate_image("./img/soldier/walk/southeast.xpm");
	_player()->walk_sprite[2] = generate_image("./img/soldier/walk/east.xpm");
	_player()->walk_sprite[3] = generate_image("./img/soldier/walk/northeast.xpm");
	_player()->walk_sprite[4] = generate_image("./img/soldier/walk/back.xpm");
	_player()->walk_sprite[5] = generate_image("./img/soldier/walk/northwest.xpm");
	_player()->walk_sprite[6] = generate_image("./img/soldier/walk/west.xpm");
	_player()->walk_sprite[7] = generate_image("./img/soldier/walk/southwest.xpm");

	_player()->death_sprite = generate_image("./img/soldier/death.xpm");

	_player()->rifle = generate_image("./img/soldier/rifle.xpm");
}


void	ft_init_player_pos(void)
{
	double	dist;

	_player()->pseudo[0] = 0;
	_player()->weapon_id = 0;
	_player()->can_shoot = 1;
	_player()->start_reload = get_clock(_var()->clock);
	_player()->health = 100;
	_player()->ammo = 0;
	_player()->x = 5;
	_player()->y = 3;
	_player()->z = 0;
	_player()->dx = -1;
	_player()->shooted.id = -1;
	_player()->shooted.shoot = 0;
	_player()->dy = 0;
	_player()->is_dead = 0;
	_player()->death_n = 0;
	_player()->plane = (t_vector2F){0, -0.66};
	_var()->time = 0;
	_var()->old_time = 0;
	_player()->hb.hit.radius = 0.5;
	_player()->hb.n = 0;
	_player()->pitch = 0;
	generate_dsprite();
	_player()->sprite = generate_image("./img/front.xpm");
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	_player()->is_walking = 0;	
}

void	walk_clock(void)
{
	if (get_clock(_var()->clock) - _var()->walk_start > 50000 )
	{
		_var()->walk_n++;
		if (_var()->walk_n >= 16)
			_var()->walk_n = 0;
		_var()->walk_start = get_clock(_var()->clock);
	}
}

void	death_clock(void)
{
	if (_player()->death_n == 15 || _player()->is_dead != 1)
		return ;
	if (get_clock(_var()->clock) - _player()->death_start > 50000 )
	{
		_player()->death_n++;
		if (_player()->death_n >= 16)
			_player()->death_n = 15;
		_player()->death_start = get_clock(_var()->clock);
	}
}

void	reload_clock(void)
{
	if (get_clock(_var()->clock) - _player()->start_reload > _var()->weapon[_player()->weapon_id].reload_ms)
		_player()->can_shoot = 1;
}

void	ft_init_player2(void)
{
	double	dist;
	int		i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		_var()->pseudo_img[i].img = NULL;
		_var()->o_player[i].weapon_id = 0;
		_var()->o_player[i].health = 100;
		_var()->o_player[i].x = 7;
		_var()->o_player[i].y = 8;
		_var()->o_player[i].z = 20;
		_var()->o_player[i].is_walking = 0;
		_var()->o_player[i].dx = -1;
		_var()->o_player[i].dy = 0;
		_var()->o_player[i].plane = (t_vector2F){0, -0.66};
		_var()->o_player[i].hb.hit.radius = 0.5;
		_var()->o_player[i].hb.n = 0;
		dist = hypot(_var()->o_player[i].dx, _var()->o_player[i].dy);
		_var()->o_player[i].angle = 360 - acos(_var()->o_player[i].dx / dist) * 180 / M_PI;	
		++i;
	}
}


void	ft_print_tab(char **s)
{
	int	i;
	int	line;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		line = ft_strlen(s[i]);
		++i;
	}
	_img()->map_width = line;
	_img()->map_height = i;
}

int	ft_hook(int keycode)
{
	get_key(keycode);
	//if (_var()->mode == GAME)
	//	ft_game_hook(keycode);
	if (_var()->mode == MENU)
		menu_hook(keycode);
	if (_var()->mode == MENU && _var()->menu->mode == MENU_PSEUDO)
		menu_hook_pseudo(keycode);
	if (_var()->mode == MENU && _var()->menu->mode == MENU_IP)
		menu_hook_ip(keycode);
	return (0);
}

int	ft_mouse_hook(int keycode)
{
	if (_var()->mode == MENU)
		menu_mouse_hook(keycode);
	return (0);
}

void	init_sync(void)
{
//	int	link;

//	link = 0;
	if (_var()->mode == GAME_START_ONLINE)
	{
//		if (send(_img()->socket, &link, sizeof(link), 0) < 0)
//			return ;
//		if (recv(_img()->socket, &link, sizeof(link), 0)< 0)
//			return ;
		_var()->mode = GAME;
	}
}

int	ft_loop_hook(void)
{
	int	pid;

	if (_var()->mode == ONLINE_START)
	{
			_img()->is_host = SERVER;
			pid = fork();
			if (pid == 0)
			{
				sleep(1);
				ft_init_client();
			}
			else
			{
				system(ft_strjoin("./server ", ft_itoa(_img()->nb_player)));
				exit(1);
			}
		_var()->mode = LOBBY_WAIT;
	}
	ft_fps();
	key_hook();
	init_sync();
	if (_var()->mode == GAME)
		ft_loop();
	else if (_var()->mode == MENU || _var()->mode == LOBBY_WAIT)
		menu_loop();
	return (0);
}

int	ft_mouse_release(int keycode)
{
	if (keycode == 1)
		_var()->key.mouse = 0;
	return (0);
}

int	ft_game(void)
{
	mlx_hook(_mlx()->mlx_win, 2, 1L << 0, &ft_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 3, 1L << 1, &ft_release, NULL);
	mlx_loop_hook(_mlx()->mlx, &ft_loop_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 5, 1L << 3, &ft_mouse_release, NULL);
	mlx_mouse_hook(_mlx()->mlx_win, &menu_mouse_hook, NULL);
	return (0);
}

void	init_key(void)
{
	_var()->key.a = 0;
	_var()->key.b = 0;
	_var()->key.c = 0;
	_var()->key.d = 0;
	_var()->key.e = 0;
	_var()->key.f = 0;
	_var()->key.g = 0;
	_var()->key.h = 0;
	_var()->key.i = 0;
	_var()->key.j = 0;
	_var()->key.k = 0;
	_var()->key.l = 0;
	_var()->key.m = 0;
	_var()->key.n = 0;
	_var()->key.o = 0;
	_var()->key.p = 0;
	_var()->key.q = 0;
	_var()->key.r = 0;
	_var()->key.s = 0;
	_var()->key.t = 0;
	_var()->key.u = 0;
	_var()->key.v = 0;
	_var()->key.w = 0;
	_var()->key.x = 0;
	_var()->key.y = 0;
	_var()->key.z = 0;
	_var()->key.one = 0;
	_var()->key.two = 0;
	_var()->key.three = 0;
	_var()->key.four = 0;
	_var()->key.five = 0;
	_var()->key.six = 0;
	_var()->key.seven = 0;
	_var()->key.eight = 0;
	_var()->key.nine = 0;
	_var()->key.zero = 0;
	_var()->key.underscore = 0;
	_var()->key.esc = 0;
	_var()->key.mouse = 0;
	_var()->key.up = 0;
	_var()->key.down = 0;
	_var()->key.left = 0;
	_var()->key.right = 0;
	_var()->key.space = 0;
}

void	init_weapons(void)
{
	_var()->weapon[0].name = malloc(sizeof(char) * 6);
	_var()->weapon[0].name = "Rifle\0";
	_var()->weapon[0].id = 0;
	_var()->weapon[0].power = 10;
	_var()->weapon[0].reload_ms = 5000;
	_var()->weapon[0].ammo = 15;
}

void	init_var(void)
{
	int	i;

	_var()->menu = malloc(sizeof(t_menu));
	_var()->mode = MENU;
	_var()->menu->mode = MENU_START;_var()->walk_n = 0;
	_var()->clock = start_clock();
	_var()->walk_start = get_clock(_var()->clock);
	i = 0;
	while (i < MAX_PLAYER)
		_var()->pseudo_img[i++].img = NULL;
	_var()->started = 0;
}

int main(int argc, char **argv)
{
	int		fd;

	(void)argc;
	init_var();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(139);
	_img()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_img()->map)
		exit(139);
	init_weapons();
	ft_print_tab(_img()->map);
	ft_init_mlx();
	ft_init_img();
	_ray();
	ft_init_player_pos();
	ft_init_player2();
	ft_malloc_map();
	init_key();
	gen_menu_images();
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
