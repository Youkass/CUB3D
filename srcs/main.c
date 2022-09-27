/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/27 12:34:02 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h>

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
	ft_pixel_put(5, 5, 0x00FF0000);
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	mlx_key_hook(_mlx()->mlx_win, test_hook, _mlx());
	sleep(10);
	mlx_loop(_mlx());
    return (0);
}
