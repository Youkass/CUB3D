/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:32:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/19 17:32:28 by denissereno      ###   ########.fr       */
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
}


void	ft_init_player_pos(void)
{
	double	dist;

	_player()->x = 5;
	_player()->y = 3;
	_player()->z = 0;
	_player()->dx = -1;
	_player()->shooted = 0;
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

void	death_clock(t_obj *pl)
{
	if (pl->death_n == 15)
		return ;
	if (get_clock(_var()->clock) - pl->death_start > 50000 )
	{
		pl->death_n++;
		if (pl->death_n >= 16)
			pl->death_n = 15;
		pl->death_start = get_clock(_var()->clock);
	}
}

void	ft_init_player2(void)
{
	double	dist;
	int		i;

	i = 0;
	while (i < _img()->nb_player)
	{
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
	return (0);
}

int	ft_mouse_hook(int keycode)
{
	if (_var()->mode == MENU)
		menu_mouse_hook(keycode);
	return (0);
}

int	ft_loop_hook(void)
{
	ft_fps();
	key_hook();
	if (_var()->mode == GAME)
		ft_loop();
	else if (_var()->mode == MENU)
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
	_var()->key.d = 0;
	_var()->key.esc = 0;
	_var()->key.mouse = 0;
	_var()->key.s = 0;
	_var()->key.w = 0;
	_var()->key.up = 0;
	_var()->key.down = 0;
	_var()->key.left = 0;
	_var()->key.right = 0;
	_var()->key.space = 0;
}

int main(int argc, char **argv)
{
	int		fd;
	int		pid;

	fd = open(argv[1], O_RDONLY);
	_var()->clock = start_clock();
	_var()->walk_start = get_clock(_var()->clock);
	if (fd < 0)
		exit(139);
	_img()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_img()->map)
		exit(139);
	if (argc == 4)
	{
		_img()->nb_player = atoi(argv[3]);
		if (atoi(argv[2]) == 1)
		{
			_img()->is_host = SERVER;
			pid = fork();
			if (pid == 0)
			{
				system(ft_strjoin("./server ", argv[3]));
				exit(1);
			}
		}
		else if (atoi(argv[2]) == 2)
			_img()->is_host = CLIENT;
	}
	sleep(1);
	ft_init_client();
	ft_print_tab(_img()->map);
	ft_init_mlx();
	ft_init_img();
	_ray();
	ft_init_player_pos();
	ft_init_player2();
	ft_malloc_map();
	init_key();
	gen_menu_images();
	_var()->mode = GAME;
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
