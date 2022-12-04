/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:53:07 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

static void	init_ray_wall(t_raycasting *r)
{
	r->cam.x = 2 * (WIN_W / 2) / (double)WIN_W - 1;
	r->dir.x = _player()->dx + _player()->plane.x * r->cam.x;
	r->dir.y = _player()->dy + _player()->plane.y * r->cam.x;
	r->map = (t_vector2D){(_player()->x + 0.5), (_player()->y + 0.5)};
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

static void	init_dda_wall(t_raycasting *r)
{
	r->hit = 0;
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (((_player()->x + 0.5)) - r->map.x) * r->delta.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1 - ((_player()->x + 0.5))) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = ((_player()->y + 0.5) - r->map.y) * r->delta.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1 - (_player()->y + 0.5)) * r->delta.y;
	}
}

static void	dda_wall(t_raycasting *r, t_vector2D *n)
{
	while (!r->hit)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta.x;
			r->map.x += r->step.x;
			r->side = 0;
			n->x++;
		}
		else
		{
			r->side_dist.y += r->delta.y;
			r->map.y += r->step.y;
			r->side = 1;
			n->y++;
		}
		if (r->map.y < _var()->map_height && r->map.y >= 0
			&& r->map.x < _var()->map_width && r->map.x >= 0
			&& is_wall(_var()->map[r->map.y][r->map.x]))
			r->hit = 1;
	}
}

int	nearest_wall3d(t_vector3F	*closest)
{
	t_raycasting	r;
	t_vector2D		n;
	t_vector2F		tmp;

	init_ray_wall(&r);
	init_dda_wall(&r);
	dda_wall(&r, &n);
	tmp = closest_point(posf(_player()->x, _player()->y), posf(_player()->x
				+ _player()->dx * _weapon()[_player()->weapon_id]->range,
				_player()->y + _player()->dy * _weapon()[_player()
				->weapon_id]->range), posf(r.map.x - 0.5, r.map.y - 0.5));
	closest->x = tmp.x;
	closest->y = tmp.y;
	if (one_dist2f(posf(_player()->x, _player()->y), tmp)
		* ((normalise_between2f(posf(-1000, 1000), posf(-1, 1),
					_player()->pitch))) > 0.5)
		return (0);
	closest->z = one_dist2f(posf(_player()->x, _player()->y), tmp)
		* -sin(normalise_between2f(posf(-960, 960), posf(-1, 1),
				_player()->pitch)) * 1000;
	return (1);
}
