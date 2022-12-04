/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:58:13 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

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
}

void	ft_intro_sprite_to_image(int i1, int i2, t_vector2D v1, t_vector2D v2)
{
	ft_put_img_to_img_scale(*_img(),
		_image()->intro_sprite[i1], v1, (t_vector2F){0.5, 0.5});
	ft_put_img_to_img_scale(*_img(),
		_image()->intro_sprite[i2], v2, (t_vector2F){0.5, 0.5});
}

void	ft_init_youri(unsigned long *start, unsigned long *c, t_vector2D *pos)
{
		pos->x = WIN_W - 350;
		pos->y = 50;
		*c = get_clock(_var()->clock);
		*start = get_clock(_var()->clock);
}
