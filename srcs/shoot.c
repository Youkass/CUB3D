/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:37:47 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/20 23:37:59 by dasereno         ###   ########.fr       */
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

//void	shoot_alone(void)
//{
//	init_shot((t_vector2F){_player()->x, _player()->y}, nearest_wall());
//}

void	shoot_alone3F(void)
{
	init_shot3F(pos3f(_player()->x, _player()->y, (_player()->z) + 100), pos3f(_player()->x
		+ _player()->dx * _weapon()[_player()->weapon_id]->range, _player()->y +
		_player()->dy * _weapon()[_player()->weapon_id]->range, _player()->z -
		((sin(normalise_between2F(posf(-960, 960), posf(-1, 1), _player()->pitch)) * 1000) * _weapon()[_player()->weapon_id]->range)));
}

/*
one_dist2F(posf(_player()->x, _player()->y), closest) * -sin(normalise_between
	2F(posf(-960, 960), posf(-1, 1), _player()->pitch)) * 1000)

This line allow us to compute the Z point of were the bullet will stop.

We already know the X and Y pos of the bullet, and to compute the Z we need
to know the distance from start to stop.

So we get this distance with the function on_dist2F. 
One dist 2F compute distance from 2 vector. So we calculate the distance
from player to the goal of the bullet.

To handle the head up and down we use a value called pitch that can variate
from -400 to 400 in game but in reality its between average -950 to 950.

So we need to convert this value to a trigonometric value. So we normalized
the pitch between -1 and 1: -1 when we look down and 1 when we look up and 0
when we look mid.

So know we need to get the minus sin of this value and we muiltiply this value
by 1000 two our Z coord scaled at the tile map to the raycasting visualisating. 

*/

void	shoot(void)
{
	int			i;
	t_vector2F	closest;
	t_vector3F	closest3F;
	int			touched;

	i = 0;
	touched = 0;
	if (_var()->nb_player == 1 && !_var()->reload_anim)
	{
		if (_player()->weapon_id != KNIFE)
			shoot_alone3F();
		_var()->shotanim_start = get_clock(_var()->clock);
		_var()->shot_anim = 1;
		return ;
	}
	while (i < _var()->linked_players)
	{
		if (_var()->o_player[i].id != _player()->id &&
			is_shoot_touch((t_vector2F){_player()->x, _player()->y},
			(t_vector2F){_player()->x + (_player()->dx * _weapon()[_player()->weapon_id]->range), _player()->y
			+ (_player()->dy * _weapon()[_player()->weapon_id]->range)}, (t_circle){(t_vector2F){_var()->o_player[i].x,
			_var()->o_player[i].y}, 0.30}, &closest) && !_var()->reload_anim)
		{
			closest3F = pos3f(closest.x, closest.y, one_dist2F(
				posf(_player()->x, _player()->y), closest) *
				-sin(normalise_between2F(posf(-960, 960), posf(-1, 1),
				_player()->pitch)) * 1000);
			if (((!_var()->o_player[i].is_crouching && closest3F.z < 450 && closest3F.z > -230)
			|| (_var()->o_player[i].is_crouching && closest3F.z > 37 && closest3F.z < 432))
			&& _var()->o_player[i].health > 0)
			{
				_player()->shooted.id = _var()->o_player[i].id;
				_player()->shooted.shoot = 1;
				if ((!_var()->o_player[i].is_crouching && closest3F.z < 40)
				|| (_var()->o_player[i].is_crouching && closest3F.z < 165)) // HEADSHOT CROUCH
				{
					if (_var()->o_player[i].health - _weapon()
						[_player()->weapon_id]->headshot <= 0)
					{
						kill_push(_var()->o_player[i].id);
						_player()->kills++;
					}
					_player()->shooted.shoot = 2;
					printf("===> HEADSHOT\n");
				}
				else if ((!_var()->o_player[i].is_crouching && closest3F.z < 235)
				|| (_var()->o_player[i].is_crouching && closest3F.z < 315)) // NORMAL
				{
					if (_var()->o_player[i].health - _weapon()
						[_player()->weapon_id]->power <= 0)
					{
						kill_push(_var()->o_player[i].id);
						_player()->kills++;
					}
					printf("===> NORMAL\n");
				}
				else // FOOTSHOT
				{
					if (_var()->o_player[i].health - _weapon()
						[_player()->weapon_id]->footshot <= 0)
					{
						kill_push(_var()->o_player[i].id);
						_player()->kills++;
					}
					_player()->shooted.shoot = 3;
					printf("===> FOOTSHOT\n");
				}
				touched = 1;
				_player()->touched = 1;
				_var()->start_touch = get_clock(_var()->clock);
				_var()->shotanim_start = get_clock(_var()->clock);
				_var()->shot_anim = 1;
				if (_player()->weapon_id != KNIFE)
					init_shot3F(pos3f(_player()->x, _player()->y, _player()->z + 100), closest3F);
			}
			break ;
		}
		i++;
	}
	if (touched == 0  && !_var()->reload_anim)
	{
		_var()->shotanim_start = get_clock(_var()->clock);
		_var()->shot_anim = 1;
		printf("===> %f\n", _var()->frame_time);
		printf("pas touchew\n");
		if (_player()->weapon_id == KNIFE)
			return ;
		if (nearest_wall3D(&closest3F))
			init_shot3F(pos3f(_player()->x, _player()->y, _player()->z + 100), closest3F);
		else
				init_shot3F(pos3f(_player()->x, _player()->y, (_player()->z) + 100), pos3f(_player()->x
		+ _player()->dx * _weapon()[_player()->weapon_id]->range, _player()->y + _player()->dy * _weapon()[_player()->weapon_id]->range, _player()->z - ((sin(normalise_between2F(posf(-960, 960), posf(-1, 1), _player()->pitch)) * 1000) * _weapon()[_player()->weapon_id]->range)));
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
			&& is_wall(_var()->map[r->map.y][r->map.x]))
			r->hit = 1;
	}
}

int	nearest_wall3D(t_vector3F	*closest)
{
	t_raycasting	r;
	t_vector2D		n;
	t_vector2F 		tmp;

	init_ray_wall(&r);
	init_dda_wall(&r);
	dda_wall(&r, &n);
	tmp = closest_point(posf(_player()->x, _player()->y), posf(_player()->x
		+ _player()->dx * _weapon()[_player()->weapon_id]->range, _player()->y + _player()->dy * _weapon()[_player()->weapon_id]->range),
		posf(r.map.x - 0.5, r.map.y - 0.5));
	closest->x = tmp.x;
	closest->y = tmp.y;
	if (one_dist2F(posf(_player()->x, _player()->y), tmp)
		* ((normalise_between2F(posf(-1000, 1000), posf(-1, 1),
		_player()->pitch))) > 0.5)
		return (0);
	closest->z =one_dist2F(posf(_player()->x, _player()->y), tmp)
		* -sin(normalise_between2F(posf(-960, 960), posf(-1, 1), _player()->pitch)) * 1000;
	return (1);
}

void	init_shot3F(t_vector3F start, t_vector3F end)
{
	int	n;

	n = _player()->shoot_n;
	_player()->shott[n].start_pos = start;
	_player()->shott[n].end_pos = end;
	_player()->shott[n].n = 0;
	_player()->shott[n].weapon_type = _player()->weapon_id;
	_player()->shott[n].shot = 1;
	_player()->shott[n].velo.dist = dist_3f(start, end);
	_player()->shott[n].velo.time_ms = (int)get_time_velo3F(one_dist2F(posf(start.x, start.y), posf(end.x, end.y)), 15000);
	_player()->shott[n].velo.velo = velocity_ms3F(_player()->shott[n].velo.dist,
		_player()->shott[n].velo.time_ms);
	_player()->shott[n].start_time = get_clock(_var()->clock);
	_player()->shott[n].pos = velocity_get_point3F(_player()->shott[n].start_pos
	, _player()->shott[n].velo.velo, get_time(_player()->shott[n].start_time));
	_player()->shoot_n++;
}
