/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/27 18:25:36 by yobougre         ###   ########.fr       */
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
    if (argc != 2)
    {
        printf("Arguments error\n");
        return (1);
    }
    (void)argv;
	ft_init_mlx();
	ft_init_img();
	ft_init_player_pos();
	if (ft_malloc_enum_key())
		return (1);
	mlx_key_hook(_mlx()->mlx_win, &ft_hook, _mlx());
	mlx_loop_hook(_mlx()->mlx, &ft_loop, NULL);
	mlx_loop(_mlx()->mlx);
    return (0);
}
