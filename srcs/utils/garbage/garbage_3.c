/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:11:10 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 20:57:45 by dasereno         ###   ########.fr       */
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
