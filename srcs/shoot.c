/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:37:47 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/30 17:25:21 by denissereno      ###   ########.fr       */
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
	int			touched;

	i = 0;
	touched = 0;
	while (i < _var()->nb_player)
	{
		if (_var()->o_player[i].id != _player()->id &&
			is_shoot_touch((t_vector2F){_player()->x, _player()->y},
			(t_vector2F){_player()->x + (_player()->dx * 30), _player()->y
			+ (_player()->dy * 30)}, (t_circle){(t_vector2F){_var()->o_player[i].x,
			_var()->o_player[i].y}, 1}, &closest))
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
		init_shot((t_vector2F){_player()->x, _player()->y},
			(t_vector2F){_player()->x + (_player()->dx * 10), _player()->y
		+ (_player()->dy * 10)});
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

void	init_shot(t_vector2F start, t_vector2F end)
{
	printf("entree\n");
	_player()->shott[_player()->shoot_n].start_pos = start;
	_player()->shott[_player()->shoot_n].end_pos = end;
	_player()->shott[_player()->shoot_n].n = 0;
	_player()->shott[_player()->shoot_n].weapon_type = _player()->weapon_id;
	_player()->shott[_player()->shoot_n].start_time = get_clock(_var()->clock);
	compute_shot(start, end);
	_player()->shott[_player()->shoot_n].pos = _player()->shott[_player()->shoot_n].n_pos[0];
	_player()->shott[_player()->shoot_n].shot = 1;
	_player()->shoot_n++;
}

// FAIRE LES SHOOTS COTE SERVEUR