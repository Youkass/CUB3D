/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 01:57:27 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/12/03 18:58:31 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_vector2D	ft_draw_youri(void)
{
	static t_vector2D		pos;
	static unsigned long	start = 0;
	static unsigned long	clock = 0;

	if (!start)
		ft_init_youri(&start, &clock, &pos);
	if (pos.x > 430)
		ft_put_image_to_image_scale(*_img(),
			_image()->intro_sprite[3], pos, (t_vector2F){0.3, 0.3});
	else
	{
		if (get_time(start) < 11008891)
			ft_put_image_to_image_scale(*_img(),
				_image()->intro_sprite[4], pos, (t_vector2F){0.3, 0.3});
		else
			ft_put_image_to_image_scale(*_img(),
				_image()->intro_sprite[5], pos, (t_vector2F){0.3, 0.3});
	}
	if (get_time(clock) > 50 && pos.x > 430)
	{
		pos.x -= 3;
		clock = get_clock(_var()->clock);
	}
	return (pos);
}

static void	ft_init_darian(unsigned long *start, unsigned long *clock,
	t_vector2D *pos)
{
		pos->x = 50;
		pos->y = 50;
		*clock = get_clock(_var()->clock);
		*start = get_clock(_var()->clock);
}

t_vector2D	ft_draw_darian(void)
{
	static t_vector2D		pos;
	static unsigned long	start = 0;
	static unsigned long	clock = 0;

	if (!start)
		ft_init_darian(&start, &clock, &pos);
	if (pos.x < WIN_W / 2)
		ft_put_image_to_image_scale(*_img(),
			_image()->intro_sprite[0], pos, (t_vector2F){0.3, 0.3});
	else
	{
		if (get_time(start) < 11008891)
			ft_put_image_to_image_scale(*_img(),
				_image()->intro_sprite[1], pos, (t_vector2F){0.3, 0.3});
		else
			ft_put_image_to_image_scale(*_img(),
				_image()->intro_sprite[2], pos, (t_vector2F){0.3, 0.3});
	}
	if (get_time(clock) > 500 && pos.x < WIN_W / 2)
	{
		pos.x += 3;
		clock = get_clock(_var()->clock);
	}
	return (pos);
}

void	ft_end_intro(t_vector2D *double_pos)
{
	static t_vector2D	pos_logo;
	static int			start = 0;

	if (!start)
	{
		pos_logo.x = WIN_W / 2 - _menu()->logo.w * 2 - 30;
		pos_logo.y = -100;
		++start;
	}
	ft_put_image_to_image_scale(*_img(),
		_menu()->logo, pos_logo,
		(t_vector2F){0.15, 0.15});
	ft_put_image_to_image_scale(*_img(),
		_image()->intro_sprite[2], double_pos[0],
		(t_vector2F){0.3, 0.3});
	ft_put_image_to_image_scale(*_img(),
		_image()->intro_sprite[5], double_pos[1],
		(t_vector2F){0.3, 0.3});
	if (double_pos[1].x > 260)
		double_pos[1].x -= 3;
	if (double_pos[0].x < 870)
		double_pos[0].x += 3;
	if (pos_logo.y < 20)
		pos_logo.y += 3;
}

void	ft_intro(void)
{
	static unsigned long	start = 0;

	if (!start)
	{
		start = get_clock(_var()->clock);
		ft_open_intro_sprites();
	}
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_draw_darian();
	ft_draw_youri();
}
