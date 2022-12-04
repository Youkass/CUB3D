/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:11:10 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 18:14:21 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	ft_black_hole(int exit_code)
{
	t_list	*tmp;
	t_list	*tmp_2;
	t_list	*tmp_3;
	t_media	*media;

	exit_say_error(exit_code);
	tmp = _lst();
	tmp_2 = _lstimg();
	ft_lstclear_img(&tmp_2);
	if (IS_MUSIC == 1)
	{
		tmp_3 = _lstmedia();
		media = _media();
		ft_lstclear_media(&tmp_3);
		ma_engine_uninit(&media->engine);
	}
	mlx_destroy_window(_mlx()->mlx, _mlx()->mlx_win);
	mlx_destroy_display(_mlx()->mlx);
	free(_mlx()->mlx);
	ft_lstclear(&tmp, free);
	pthread_exit(0);
	exit(exit_code);
}

void	exit_say_error_2(int exit_code)
{
	if (exit_code == 18)
		printf("Error\nUnrecognized token\n");
	else if (exit_code == 19)
		printf("Error\nMap is not closed");
	else if (exit_code == 20)
		printf("Error\nInvalid path\n");
	else if (exit_code == 21)
		printf("Error\nInvalid syntax\n");
	else if (exit_code == 22)
		printf("Error\nWrong teams positions given\n");
}

void	exit_say_error(int exit_code)
{
	if (exit_code == 11)
		printf("Error\nInvalid numbers of arguments\n");
	else if (exit_code == 10)
		printf("Error\nMap to big: Max 1024 * 1024\n");
	else if (exit_code == 12)
		printf("Error\nMap not closed\n");
	else if (exit_code == 13)
		printf("Error\nInvalid numbers of arguments\n");
	else if (exit_code == 14)
		printf("Error\nUnrecognized argument\n");
	else if (exit_code == 15)
		printf("Error\nInvalid numbers of arguments\n");
	else if (exit_code == 16)
		printf("Error\nNumber not in color range (0-255)\n");
	else if (exit_code == 17)
		printf("Error\nToo many instructions\n");
	else
		exit_say_error_2(exit_code);
}
