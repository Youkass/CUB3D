/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 11:21:00 by denissereno      ###   ########.fr       */
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
	if (ft_malloc_enum_key())
		return (1);
	gen_menu_images();
	ft_pixel_put(5, 5, 0x00FF0000);
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _var()->menu->buttons[0][1].img, 0, 0);
	//mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	mlx_key_hook(_mlx()->mlx_win, ft_hook, _mlx());
	mlx_loop(_mlx()->mlx);
    return (0);
}
