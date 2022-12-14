/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:32:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/05 21:05:53 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes_bonus/cub.h"

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
	mlx_hook(_mlx()->mlx_win, 17, 0, ft_escape, NULL);
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

int	main(int argc, char **argv)
{
	int		fd;
	char	**buf;

	if (argc != 2)
	{
		printf("Error\nInvalid numbers of arguments\n");
		exit(0);
	}
	fd = ft_check_map_name(argv[1]);
	if (fd < 0)
		return (1);
	_lst();
	init_var();
	ft_init_mlx();
	buf = ft_split(read_file(fd), '\n');
	parse_args(buf);
	ft_call_functions();
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
