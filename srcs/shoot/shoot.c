/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:37:47 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/01 16:41:15 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_player_can_kill(int i, t_vector2F *closest)
{
	if (_var()->o_player[i].id != _player()->id
		&& is_shoot_touch((t_vector2F){_player()->x, _player()->y},
		(t_vector2F){_player()->x + (_player()->dx * _weapon()[_player()
			->weapon_id]->range), _player()->y + (_player()->dy * _weapon()
			[_player()->weapon_id]->range)}, (t_circle){(t_vector2F)
			{_var()->o_player[i].x,
		_var()->o_player[i].y}, 0.30}, closest) && !_var()->reload_anim
		&& is_wall_closest(*closest))
		return (1);
	return (0);
}

void	no_player_touched(int touched, t_vector3F closest3f)
{
	if (touched == 0 && !_var()->reload_anim && _var()->linked_players > 1)
	{
		_var()->shotanim_start = get_clock(_var()->clock);
		_var()->shot_anim = 1;
		if (_player()->weapon_id == KNIFE)
			return ;
		if (nearest_wall3d(&closest3f))
			init_shot3f(pos3f(_player()->x, _player()->y, _player()->z + 100),
				closest3f);
		else
			init_shot3f(pos3f(_player()->x, _player()->y, (_player()->z) + 100),
				pos3f(_player()->x + _player()->dx * _weapon()[_player()
					->weapon_id]->range, _player()->y + _player()->dy
					* _weapon()[_player()->weapon_id]->range, _player()->z
					- ((sin(normalise_between2F(posf(-960, 960), posf(-1, 1),
									_player()->pitch)) * 1000) * _weapon()
					[_player()->weapon_id]->range)));
	}
}

void	singleplayer_shoot(void)
{
	if (_var()->nb_player == 1 && !_var()->reload_anim)
	{
		if (_player()->weapon_id != KNIFE)
			shoot_alone3f();
		_var()->shotanim_start = get_clock(_var()->clock);
		_var()->shot_anim = 1;
		return ;
	}
}

void	shoot(void)
{
	int			i;
	t_vector2F	closest;
	t_vector3F	closest3f;
	int			touched;

	i = 0;
	touched = 0;
	closest = posf(0, 0);
	singleplayer_shoot();
	while (i < _var()->linked_players)
	{
		if (is_player_can_kill(i, &closest))
		{
			closest3f = pos3f(closest.x, closest.y, one_dist2F(
						posf(_player()->x, _player()->y), closest)
					* -sin(normalise_between2F(posf(-960, 960), posf(-1, 1),
							_player()->pitch)) * 1000);
			if (is_touch_pl(closest3f, _var()->o_player[i]))
				shoot_touched(i, &touched, closest3f);
			break ;
		}
		i++;
	}
	no_player_touched(touched, closest3f);
}

void	init_shot3f(t_vector3F start, t_vector3F end)
{
	int			n;
	t_vector3F	dist;
	int			time_vel;

	dist = dist_3f(start, end);
	time_vel = (int)get_time_velo3F(one_dist2F(posf(start.x, start.y),
				posf(end.x, end.y)), 15000);
	n = _player()->shoot_n;
	_player()->shott[n].start_pos = start;
	_player()->shott[n].end_pos = end;
	_player()->shott[n].n = 0;
	_player()->shott[n].weapon_type = _player()->weapon_id;
	_player()->shott[n].shot = 1;
	_player()->shott[n].velo.dist = dist;
	_player()->shott[n].velo.time_ms = time_vel;
	dist = velocity_ms3F(dist, time_vel);
	_player()->shott[n].velo.velo = dist;
	_player()->shott[n].start_time = get_clock(_var()->clock);
	dist = velocity_get_point3F(start, dist,
			get_time(get_clock(_var()->clock)));
	_player()->shott[n].pos = dist;
	_player()->shoot_n++;
}
