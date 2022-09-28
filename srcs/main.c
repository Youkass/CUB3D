/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 11:09:47 by yobougre         ###   ########.fr       */
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
	mlx_key_hook(_mlx()->mlx_win, &ft_hook, _mlx());
	mlx_loop_hook(_mlx()->mlx, &ft_loop, NULL);
	mlx_loop(_mlx()->mlx);
    return (0);
}
