/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 12:34:03 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h>

void	ft_init_player_pos(void)
{
	_player()->x = 300;
	_player()->y = 300;
}

int main(int argc, char **argv)
{
	(void)argc;
    (void)argv;
	ft_init_mlx();
	ft_init_img();
	ft_init_player_pos();
	gen_menu_images();
	mlx_hook(_mlx()->mlx_win, 2, 1L<<0, &ft_hook, _mlx());
	mlx_loop_hook(_mlx()->mlx, &ft_loop, NULL);
	mlx_loop(_mlx()->mlx);
    return (0);
}
