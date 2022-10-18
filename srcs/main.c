/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */ /*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/07 02:03:34 by denissereno      ###   ########.fr       */
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
		_var()->key.w = 0;
	if (keycode == S)
		_var()->key.s = 0;
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

void	ft_init_player_pos(void)
{
	double	dist;

	_player()->x = 5;
	_player()->y = 3;
	_player()->z = 0;
	_player()->dx = -1;
	_player()->dy = 0;
	_player()->plane = (t_vector2F){0, -0.66};
	_var()->time = 0;
	_var()->old_time = 0;
	_player()->hb.hit.radius = 0.5;
	_player()->hb.n = 0;
	_player()->pitch = 0;
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;	
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
		_var()->o_player[i].dx = -1;
		_var()->o_player[i].dy = 0;
		_var()->o_player[i].sprite = generate_image("./img/front.xpm");
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

	fd = open(argv[1], O_RDONLY);
	_var()->clock = start_clock();
	if (fd < 0)
		exit(139);
	_img()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_img()->map)
		exit(139);
	if (argc == 4)
	{
		if (atoi(argv[2]) == 1)
		{
			_img()->is_host = SERVER;
			system(ft_strjoin("./server ", argv[3]));
		}
		else if (atoi(argv[2]) == 2)
			_img()->is_host = CLIENT;
		_img()->nb_player = atoi(argv[3]);
	}
	ft_print_tab(_img()->map);
	ft_init_mlx();
	ft_init_img();
	_ray();
	ft_init_player_pos();
	ft_init_player2();
	ft_malloc_map();
	init_key();
	gen_menu_images();
	_var()->mode = MENU;
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
