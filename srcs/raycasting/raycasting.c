/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/29 19:01:00 by dasereno         ###   ########.fr       */
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

void	dda(t_raycasting *r)
{
	while (!r->hit)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (r->map.y < _var()->map_height && r->map.y >= 0
			&& r->map.x < (int)ft_strlen(_var()->map[r->map.y]) && r->map.x >= 0
			&& is_wall(_var()->map[r->map.y][r->map.x]))
		{
			if (_var()->map[r->map.y][r->map.x] >= '2' &&
			_var()->map[r->map.y][r->map.x] <= '9')
				r->tex_i = _var()->map[r->map.y][r->map.x] - 48;
			else if (_var()->map[r->map.y][r->map.x] >= 'A' &&
			_var()->map[r->map.y][r->map.x] <= 'B')
				r->tex_i = _var()->map[r->map.y][r->map.x] - 57;
			else
				r->tex_i = -1;
			r->hit = 1;
		}
	}
}

void	compute_drawing_data(t_raycasting *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist.x - r->delta.x);
	else
		r->perp_wall_dist = (r->side_dist.y - r->delta.y);
	r->line_h = (int)(WIN_H / r->perp_wall_dist);
	r->draw_start = (-r->line_h / 2 + WIN_H / 2) + r->pl.pitch
		+ (r->pl.z / r->perp_wall_dist);
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = (r->line_h / 2 + WIN_H / 2) + r->pl.pitch
		+ (r->pl.z / r->perp_wall_dist);
	if (r->draw_end > WIN_H)
		r->draw_end = WIN_H - 1;
	if (r->side == 0)
		r->wall_x = (r->pl.y + 0.5) + r->perp_wall_dist * r->dir.y;
	else
		r->wall_x = (r->pl.x + 0.5) + r->perp_wall_dist * r->dir.x;
	r->wall_x -= floor(r->wall_x);
}

void	draw_wall(t_raycasting *r)
{
	r->tex.x = (int){r->wall_x * 64.0};
	if (r->side == 0 && r->dir.x > 0)
		r->tex.x = 64 - r->tex.x - 1;
	else if (r->side == 1 && r->dir.y < 0)
		r->tex.x = 64 - r->tex.x - 1;
	r->tex_step = 1.0 * 64 / r->line_h;
	r->tex_pos = (r->draw_start - r->pl.pitch - (r->pl.z / r->perp_wall_dist)
			- WIN_H / 2 + r->line_h / 2) * r->tex_step;
	r->y = r->draw_start;
	while (r->y < r->draw_end)
	{
		r->tex.y = (int)r->tex_pos & (128 - 1);
		r->tex_pos += r->tex_step;
		if (r->tex_i < 0 || r->tex_i > 9)
			ft_put_pixel(_img(), &_menu()->wall, pos(r->x, r->y),
				pos(r->tex.x, r->tex.y));
		else
			ft_put_pixel(_img(), &_image()->textures[r->tex_i],
				pos(r->x, r->y), pos(r->tex.x, r->tex.y));
		r->y++;
	}
}

void	*ray_draw(void *t)
{
	t_ray_th	r;

	r = *(t_ray_th *)t;
	_ray()[r.i]->x = r.start_end.x;
	if (_player()->spectate && _player()->spec_id >= 0
		&& _player()->spec_id <= _var()->nb_player)
		_ray()[r.i]->pl = _var()->o_player[_player()->spec_id];
	else
		_ray()[r.i]->pl = r.pl;
	while (_ray()[r.i]->x < r.start_end.y)
	{
		init_ray(_ray()[r.i]);
		init_dda(_ray()[r.i]);
		dda(_ray()[r.i]);
		if (_ray()[r.i]->hit == 0)
			continue ;
		compute_drawing_data(_ray()[r.i]);
		draw_wall(_ray()[r.i]);
		_var()->zbuffer[_ray()[r.i]->x] = _ray()[r.i]->perp_wall_dist;
		_ray()[r.i]->x++;
	}
	return (NULL);
}

/*
-Algorithm to draw raycasting.
*/

void	draw_rays(void)
{
	static t_ray_th	r[TH_RAY];
	static int		started = 0;
	int				i;

	if (!started)
	{
		i = 0;
		while (i < TH_RAY)
		{
			r[i].start_end = (t_vector2D){(WIN_W / TH_RAY) * i,
				(WIN_W / TH_RAY) * (i + 1)};
			r[i].i = i;
			i++;
		}
	}
	i = 0;
	while (i < TH_RAY)
	{
		r[i].pl = *_player();
		pthread_create(&_var()->th[i], NULL, ray_draw, &r[i]);
		i++;
	}
	while (i)
		pthread_join(_var()->th[i--], NULL);
}
