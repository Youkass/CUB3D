/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/26 17:40:34 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
-Singleton for the image
*/
t_data	*_img()
{
	static t_data	img;

	return (&img);
}

/*
-Singleton for the mlx datas
*/
t_mlx	*_mlx()
{
	static t_mlx	mlx;

	return (&mlx);
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

    return (0);
}
