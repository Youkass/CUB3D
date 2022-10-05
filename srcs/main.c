/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/05 18:38:54 by denissereno      ###   ########.fr       */
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
	return (0);
}

void	ft_init_player_pos(void)
{
	//_player()->angle = 0;
	_player()->x = 5;
	_player()->y = 3;
	_player()->dx = -1;
	_player()->dy = 0;
	//for (int i = 0; i < 10; i++)
	//{
	//	_ray()[i]->max_y = -1;
	//	_ray()[i]->min_y = -1;
	//}
	_player()->plane = (t_vector2F){0, -0.66};
	_var()->time = 0;
	_var()->old_time = 0;
	_player()->hb.hit.radius = 0.5;
	_player()->hb.n = 0;

	
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
	ft_print_tab(_img()->map);
	(void)argc;
	ft_init_mlx();
	ft_init_img();
	_ray();
	ft_init_player_pos();
	ft_malloc_map();
	init_key();
	gen_menu_images();
	_var()->mode = GAME;
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
