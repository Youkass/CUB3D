/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 14:55:19 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h>

void	ft_init_player_pos(void)
{
	_player()->x = 300;
	_player()->y = 300;
}

void	ft_print_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		++i;
	}
	_img()->map_height = i;
}

int main(int argc, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(139);
	_img()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_img()->map)
		exit(139);
	ft_print_tab(_img()->map);
	(void)argc;
	ft_init_mlx();
	ft_init_img();
	ft_init_player_pos();
	gen_menu_images();
	mlx_hook(_mlx()->mlx_win, 2, 1L<<0, &ft_hook, _mlx());
	mlx_loop_hook(_mlx()->mlx, &ft_loop, NULL);
	mlx_loop(_mlx()->mlx);
    return (0);
}
