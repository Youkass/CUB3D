/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:47:58 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 14:53:57 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_vector2F	closest_point(t_vector2F a, t_vector2F b, t_vector2F c)
{
	float	delta_s;

	delta_s = fdot(sub_2f(c, a), sub_2f(b, a))
		/ fdot(sub_2f(b, a), sub_2f(b, a));
	if (delta_s <= 0)
		return (a);
	else if (delta_s >= 1)
		return (b);
	else
		return ((t_vector2F){a.x + (delta_s * b.x) - (delta_s * a.x), a.y
			+ (delta_s * b.y) - (delta_s * a.y)});
}

void	push_and_kill(int i)
{
	kill_push(_var()->o_player[i].id);
	_player()->kills++;
}

void	shoot_type(int type, int i)
{
	if (type == 2)
	{
		if (_var()->o_player[i].health - _weapon()
			[_player()->weapon_id]->headshot <= 0)
			push_and_kill(i);
		_player()->shooted.shoot = type;
	}
	else if (type == 1)
	{
		if (_var()->o_player[i].health - _weapon()
			[_player()->weapon_id]->power <= 0)
			push_and_kill(i);
		_player()->shooted.shoot = type;
	}
	else
	{
		if (_var()->o_player[i].health - _weapon()
			[_player()->weapon_id]->footshot <= 0)
			push_and_kill(i);
		_player()->shooted.shoot = 3;
	}
}

int	is_shoot_touch(t_vector2F a, t_vector2F b, t_circle c, t_vector2F *closest)
{
	float		r2;
	float		len;
	t_vector2F	n;
	float		dist;
	float		index;

	*closest = closest_point(a, b, c.pos);
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
	index = (a.x * (a.x - b.x) + a.y * (a.y - b.y));
	return (!(index < 0 || index > len));
}

int	is_touch_pl(t_vector3F closest3f, t_obj player)
{
	if (((!player.is_crouching && closest3f.z < 450 && closest3f.z
				> -230) || (player.is_crouching && closest3f.z > 37
				&& closest3f.z < 432)) && player.health > 0)
		return (1);
	return (0);
}
