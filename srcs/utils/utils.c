/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:57:50 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/29 18:12:22 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_pixel_put(float x, float y, int color)
{
	t_data	*img;
	char	*dst;

	img = _img();
	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H)
		return ;
	dst = img->addr + (int)(y * img->line_length + x
			* (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b)
{
	if (b->addr[((pos_b.y * b->line_length) + (pos_b.x * 4)) + 3] != -1)
	{
		a->addr[pos_a.y * a->line_length + pos_a.x * 4] = b->addr
		[(pos_b.y * b->line_length) + (pos_b.x * 4)];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 1]
			= b->addr[((pos_b.y * b->line_length) + (pos_b.x * 4)) + 1];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 2]
			= b->addr[((pos_b.y * b->line_length) + (pos_b.x * 4)) + 2];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 3]
			= b->addr[((pos_b.y * b->line_length) + (pos_b.x * 4)) + 3];
	}
}

void	get_key(int keycode)
{
	if (keycode == A)
		_var()->key.a = 1;
	if (keycode == W)
		_var()->key.w = 1;
	if (keycode == S)
		_var()->key.s = 1;
	if (keycode == D)
		_var()->key.d = 1;
	if (keycode == ESC)
		_var()->key.esc = 1;
	if (keycode == LEFT)
		_var()->key.left = 1;
	if (keycode == RIGHT)
		_var()->key.right = 1;
}

int	ft_release(int keycode)
{
	if (keycode == A)
		_var()->key.a = 0;
	if (keycode == W)
		_var()->key.w = 0;
	if (keycode == S)
		_var()->key.s = 0;
	if (keycode == D)
		_var()->key.d = 0;
	if (keycode == ESC)
		_var()->key.esc = 0;
	if (keycode == LEFT)
		_var()->key.left = 0;
	if (keycode == RIGHT)
		_var()->key.right = 0;
	return (0);
}

void	ft_put_pixel_color(t_data *a, unsigned char color[4], int x, int y)
{
	if (color[3] != 255)
	{
		a->addr[y * a->line_length + x * 4] = color[0];
		a->addr[(y * a->line_length + x * 4) + 1] = color[1];
		a->addr[(y * a->line_length + x * 4) + 2] = color[2];
		a->addr[(y * a->line_length + x * 4) + 3] = color[3];
	}
}
