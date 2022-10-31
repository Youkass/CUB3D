/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:37:47 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/01 00:31:00 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


t_vector2F	closest_point(t_vector2F a, t_vector2F b, t_vector2F c)
{
	float	delta_s;

	delta_s = fdot(sub_2f(c, a), sub_2f(b, a)) / fdot(sub_2f(b, a), sub_2f(b, a));
	if (delta_s <= 0)
		return (a);
	else if (delta_s >= 1)
		return (b);
	else
		return ((t_vector2F){a.x + (delta_s * b.x) - (delta_s * a.x), a.y + (delta_s * b.y) - (delta_s * a.y)});
}

int	is_shoot_touch(t_vector2F a, t_vector2F b, t_circle c, t_vector2F *closest)
{
	float		r2;
	float		len;
	t_vector2F	n;
	float		dist;
	float		index;

	*closest =  closest_point(a, b, c.pos);
	a = (t_vector2F){a.x - c.pos.x, a.y - c.pos.y};
	b = (t_vector2F){b.x - c.pos.x, b.y - c.pos.y};
	r2 = c.r * c.r;
	if (a.x * a.x + a.y * a.y <= r2)
		return (1);
	if (b.x * b.x + b.y * b.y <= r2)
		return (1);
	len = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	n.x = b.y - a.y;
	n.y = a.x - b.x;
	dist = n.x * a.x + n.y * a.y;
	dist = dist * dist;
	if (dist > len * r2)
		return (0);
	index = (a.x*(a.x - b.x) + a.y*(a.y - b.y));
	if (index < 0)
		return (0);
	if (index > len)
		return (0);	
	return (1);
}

void	shoot_alone(void)
{
	init_shot((t_vector2F){_player()->x, _player()->y}, nearest_wall());
}

void	shoot(void)
{
	int			i;
	t_vector2F	closest;
	int			touched;

	i = 0;
	touched = 0;
	if (_var()->nb_player == 1)
	{
		shoot_alone();
		return ;
	}
	while (i < _var()->nb_player)
	{
		if (_var()->o_player[i].id != _player()->id &&
			is_shoot_touch((t_vector2F){_player()->x, _player()->y},
			(t_vector2F){_player()->x + (_player()->dx * _var()->weapon[_player()->weapon_id].range), _player()->y
			+ (_player()->dy * _var()->weapon[_player()->weapon_id].range)}, (t_circle){(t_vector2F){_var()->o_player[i].x,
			_var()->o_player[i].y}, 0.30}, &closest))
		{
			_player()->shooted.id = _var()->o_player[i].id;
			_player()->shooted.shoot = 1;
			init_shot((t_vector2F){_player()->x, _player()->y}, closest);
			touched = 1;
			break ;
		}
		i++;
	}
	if (touched == 0)
		init_shot((t_vector2F){_player()->x, _player()->y}, nearest_wall());
}

void	compute_shot(t_vector2F start, t_vector2F end)
{
	t_vector2F	distance;
	t_vector2F	nstep;
	int	i;

	distance.x = end.x - start.x;
	distance.y = end.y - start.y;
	nstep.x = distance.x / SHOT_FRAME;
	nstep.y = distance.y / SHOT_FRAME;
	i = 0;
	while (i < SHOT_FRAME)
	{
		_player()->shott[_player()->shoot_n].n_pos[i] = start;
		start = add_2f(start, nstep);
		i++;
	}
}

static void	init_ray_wall(t_raycasting *r)
{
	r->cam.x = 2 * (WIN_W / 2) / (double)WIN_W - 1;
	r->dir.x =  _player()->dx + _player()->plane.x * r->cam.x;
	r->dir.y =  _player()->dy + _player()->plane.y * r->cam.x;
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
		if (r->map.y < _var()->map_height && r->map.y >= 0 &&
			r->map.x < _var()->map_width && r->map.x >= 0
			&& _var()->map[r->map.y][r->map.x] == '1')
			r->hit = 1;
	}
}

t_vector2F	nearest_wall()
{
	t_raycasting	r;
	t_vector2D		n;

	printf("alqaida\n");
	init_ray_wall(&r);
	init_dda_wall(&r);
	dda_wall(&r, &n);
	return (posf(r.map.x, r.map.y));
}

void	init_shot(t_vector2F start, t_vector2F end)
{
	int	n;

	n = _player()->shoot_n;
	_player()->shott[n].start_pos = start;
	_player()->shott[n].end_pos = end;
	_player()->shott[n].n = 0;
	_player()->shott[n].weapon_type = _player()->weapon_id;
	_player()->shott[n].start_time = get_clock(_var()->clock);
	compute_shot(start, end);
	_player()->shott[n].pos = _player()->shott[n].n_pos[0];
	_player()->shott[n].shot = 1;
	_player()->shott[n].velo.dist = dist_2f(start, end);
	_player()->shott[n].velo.time_ms = 100000;
	_player()->shott[n].velo.velo = velocity_ms(_player()->shott[n].velo.dist,
		100000);
	_player()->shoot_n++;
}

// FAIRE LES SHOOTS COTE SERVEUR