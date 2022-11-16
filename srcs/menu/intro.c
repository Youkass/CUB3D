/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 01:57:27 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/11/16 02:36:42 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_open_intro_sprites(void)
{
	_image()->intro_sprite[0] = generate_image("./img/intro/darian_1.xpm");
	_image()->intro_sprite[1] = generate_image("./img/intro/darian_2.xpm");
	_image()->intro_sprite[2] = generate_image("./img/intro/darian_3.xpm");
	_image()->intro_sprite[3] = generate_image("./img/intro/youri_1.xpm");
	_image()->intro_sprite[4] = generate_image("./img/intro/youri_2.xpm");
	_image()->intro_sprite[5] = generate_image("./img/intro/youri_3.xpm");
	_image()->intro_sprite[6] = generate_image("./img/intro/us_1.xpm");
	_image()->intro_sprite[7] = generate_image("./img/intro/us_2.xpm");
	printf("NTM\n");
}

void	ft_intro_sprite_to_image(int i1, int i2, t_vector2D v1, t_vector2D v2)
{
	ft_put_image_to_image_scale(*_img(),
		_image()->intro_sprite[i1], v1, (t_vector2F){0.5, 0.5});
	ft_put_image_to_image_scale(*_img(),
		_image()->intro_sprite[i2], v2, (t_vector2F){0.5, 0.5});
}

void	ft_intro(void)
{
	static unsigned long	start = 0;
	static unsigned long	check = 0;
	static t_vector2D		double_pos[2];
	int						limite;

	if (!start)
	{
		start = get_clock(_var()->clock);
		ft_open_intro_sprites();
		double_pos[0].x = -100;
		double_pos[0].y = 240;
		double_pos[1].x = WIN_W + 100; 
		double_pos[1].y = 240;
		limite = (WIN_W / 8);
	}
	if (double_pos[0].x < limite)
		ft_intro_sprite_to_image(3, 0, double_pos[0], double_pos[1]);
	else if (double_pos[0].x > limite && double_pos[0].x < limite * 2)
		ft_intro_sprite_to_image(4, 1, double_pos[0], double_pos[1]);
	else if (double_pos[0].x > limite * 2 && double_pos[0].x < limite * 3)
		ft_intro_sprite_to_image(5, 2, double_pos[0], double_pos[1]);
	else
	{
		double_pos[0].x = WIN_W / 2 - _image()->intro_sprite[6].w ;
		if (!check)
			check = get_clock(_var()->clock);
		if (get_time(check) < 20000)
			ft_put_image_to_image_scale(*_img(),
				_image()->intro_sprite[6], double_pos[0], (t_vector2F){0.5, 0.5});
		else
			ft_put_image_to_image_scale(*_img(),
				_image()->intro_sprite[7], double_pos[0], (t_vector2F){0.5, 0.5});
	}
	if (get_time(start) > 10000)
	{
		++double_pos[0].x;
		--double_pos[1].x;
		start = get_clock(_var()->clock);
	}
}
