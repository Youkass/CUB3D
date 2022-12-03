/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:32:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/03 20:28:27 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/cub.h"

void	ft_print_tab(char **s)
{
	int	i;
	int	line;

	i = 0;
	while (_var()->map[i])
	{
		printf("%s\n", s[i]);
		line = ft_strlen(s[i]);
		++i;
	}
	_var()->map_width = line;
	_var()->map_height = i;
}

int	ft_game(void)
{
	mlx_hook(_mlx()->mlx_win, 2, 1L << 0, &ft_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 3, 1L << 1, &ft_release, NULL);
	mlx_loop_hook(_mlx()->mlx, &ft_loop_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 5, 1L << 3, &ft_mouse_release, NULL);
	mlx_mouse_hook(_mlx()->mlx_win, &menu_mouse_hook, NULL);
	mlx_expose_hook(_mlx()->mlx_win, ft_expose, &_var()->mode);
	return (0);
}

static void	ft_call_functions(void)
{
	init_weapons();
	ft_init_media();
	ft_init_img();
	_ray();
	ft_init_player_pos();
	ft_init_player2();
	init_key();
	_menu()->n_ip = 0;
	gen_menu_images();
	init_image();
}

void	ft_print_map(void)
{
	int	i;
	int	j;

	i = 0;
	printf("print_mao\n");
	while (i < _var()->map_height)
	{
		j = 0;
		while (j < _var()->map_width)
			printf("%c", _var()->map[i][j++]);
		printf("\n");
		++i;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	char	**buf;

	(void)argc;
	fd = ft_check_map_name(argv[1]);
	if (fd < 0)
		return (1);
	init_var();
	ft_init_mlx();
	buf = ft_split(read_file(fd), '\n');
	parse_args(buf);
	ft_call_functions();
	ft_game();
	ft_print_map();
	mlx_loop(_mlx()->mlx);
	return (0);
}
