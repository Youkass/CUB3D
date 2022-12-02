/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:04:04 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 17:06:40 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_ray(t_raycasting *r)
{
	r->draw_end = 0;
	r->draw_start = 0;
	r->cam.x = 2 * r->x / (double)WIN_W - 1;
	r->dir.x = r->pl.dx + r->pl.plane.x * r->cam.x;
	r->dir.y = r->pl.dy + r->pl.plane.y * r->cam.x;
	r->map = (t_vector2D){(r->pl.x + 0.5), (r->pl.y + 0.5)};
	if (r->dir.y == 0)
		r->delta.x = 0;
	else if (r->dir.x == 0)
		r->delta.x = 1;
	else
		r->delta.x = fabs(1 / r->dir.x);
	if (r->dir.x == 0)
		r->delta.y = 0;
	else if (r->dir.y == 0)
		r->delta.y = 1;
	else
		r->delta.y = fabs(1 / r->dir.y);
}

void	init_dda(t_raycasting *r)
{
	r->hit = 0;
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (((r->pl.x + 0.5)) - r->map.x) * r->delta.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1 - ((r->pl.x + 0.5))) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = ((r->pl.y + 0.5) - r->map.y) * r->delta.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1 - (r->pl.y + 0.5)) * r->delta.y;
	}
}

void	cast_bullet(t_obj player, int i)
{
	int	j;

	j = 0;
	if (i == player.id)
	{
		j = 0;
		while (j < player.shoot_n)
		{
			init_cast_bul(j, &player, &player);
			draw_bul();
			j++;
		}	
	}
	j = 0;
	while (j < _var()->o_player[i].shoot_n)
	{
		if (_var()->o_player[i].id != _player()->id)
		{
			init_cast_bul(j, &_var()->o_player[i], &player);
			draw_bul();
		}
		j++;
	}
}

void	dda_condition(t_raycasting *r)
{
	if (r->map.y < _var()->map_height && r->map.y >= 0
		&& r->map.x < (int)ft_strlen(_var()->map[r->map.y]) && r->map.x >= 0
		&& is_wall(_var()->map[r->map.y][r->map.x]))
	{
		if (_var()->map[r->map.y][r->map.x] >= '2'
			&& _var()->map[r->map.y][r->map.x] <= '9')
			r->tex_i = _var()->map[r->map.y][r->map.x] - 48;
		else if (_var()->map[r->map.y][r->map.x] >= 'A'
			&& _var()->map[r->map.y][r->map.x] <= 'B')
			r->tex_i = _var()->map[r->map.y][r->map.x] - 57;
		else
			r->tex_i = -1;
		r->hit = 1;
	}
}
