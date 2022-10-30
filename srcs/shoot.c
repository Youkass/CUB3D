/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:37:47 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/30 02:16:30 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


t_vector2F	closest_point(t_vector2F a, t_vector2F b, t_vector2F c)
{
	float	delta_s;

	// X = c, P = a, Q = b
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

void	shoot(void)
{
	int			i;
	t_vector2F	closest;

	i = 0;
	while (i < _img()->nb_player)
	{
		if (_var()->o_player[i].id != _player()->id &&
			is_shoot_touch((t_vector2F){_player()->x, _player()->y},
			(t_vector2F){_player()->x + (_player()->dx * 150), _player()->y
			+ (_player()->dy * 150)}, (t_circle){(t_vector2F){_var()->o_player[i].x,
			_var()->o_player[i].y}, 1}, &closest))
		{
			_player()->shooted.id = _var()->o_player[i].id;
			_player()->shooted.shoot = 1;
			init_shot((t_vector2F){_player()->x, _player()->y}, closest);
			//init_shot((t_vector2F){_player()->x, _player()->y},
			//	(t_vector2F){_player()->x + (_player()->dx * 20), _player()->y
			//+ (_player()->dy * 20)});
		}
		else
			init_shot((t_vector2F){_player()->x, _player()->y},
				(t_vector2F){_player()->x + (_player()->dx * 20), _player()->y
			+ (_player()->dy * 20)});
			
		i++;
	}
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
		_var()->shott.n_pos[i] = start;
		start = add_2f(start, nstep);
		i++;
	}
}

void	init_shot(t_vector2F start, t_vector2F end)
{
	//t_vector2F	mid;
	//t_vector2F	up_quart;
	//t_vector2F	down_quart;

	_var()->shott.start_pos = start;
	_var()->shott.end_pos = end;
	_var()->shott.n = 0;
	_var()->shott.weapon_type = _player()->weapon_id;
	_var()->shott.start_time = get_clock(_var()->clock);
	compute_shot(start, end);
	//mid =  (t_vector2F){( start.x + end.x) / 2, ( start.y + end.y) / 2};
	//up_quart = (t_vector2F){(end.x + mid.x) / 2,(end.y + mid.y) / 2};
	//down_quart = (t_vector2F){(start.x + mid.x) / 2,(start.y + mid.y) / 2};
	//_var()->shott.n_pos[0] = (t_vector2F){start.x + _player()->dx, start.y + _player()->dy};
	////_var()->shott.n_pos[0] = (t_vector2F){(start.x + down_quart.x) / 2,(start.y + down_quart.y) / 2};
	//_var()->shott.n_pos[1] = (t_vector2F){(mid.x + down_quart.x) / 2,(mid.y + down_quart.y) / 2};
	////_var()->shott.n_pos[1] = down_quart;
	//_var()->shott.n_pos[2] = mid;
	//_var()->shott.n_pos[3] = up_quart;
	//_var()->shott.n_pos[4] = (t_vector2F){(mid.x + up_quart.x) / 2,(mid.y + up_quart.y) / 2};;
	////_var()->shott.n_pos[4] = (t_vector2F){(end.x + up_quart.x) / 2,(end.y + up_quart.y) / 2};;
	_var()->shott.pos = _var()->shott.n_pos[0];
	_var()->shott.shot = 1;
	//return (shot);
}

// FAIRE LES SHOOTS COTE SERVEUR