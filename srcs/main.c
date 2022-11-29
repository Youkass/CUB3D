/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/29 18:23:57 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h>

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
	return (0);
}

void	init_key(void)
{
	_var()->key.a = 0;
	_var()->key.d = 0;
	_var()->key.esc = 0;
	_var()->key.left = 0;
	_var()->key.right = 0;
	_var()->key.mouse = 0;
	_var()->key.s = 0;
	_var()->key.w = 0;
}

t_data	generate_image(char *path)
{
	t_data	sprite;

	memset(&sprite, 0, sizeof(t_data));
	if (!path)
		return (sprite);
	sprite.img = mlx_xpm_file_to_image(_mlx()->mlx, path,
			&sprite.width, &sprite.height);
	if (!sprite.img)
		return (sprite);
	sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel,
			&sprite.line_length, &sprite.endian);
	return (sprite);
}

int	main(int argc, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	_ray()->clock = start_clock();
	if (fd < 0)
		ft_black_hole(139);
	ft_init_mlx();
	parse_args(ft_split(read_file(fd), '\n'));
	if (!_img()->map)
		ft_black_hole(139);
	(void)argc;
	ft_init_img();
	ft_init_player_pos();
	init_key();
	_var()->mode = GAME;
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
