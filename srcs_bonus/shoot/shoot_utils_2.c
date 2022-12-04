/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:49:57 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	shoot_alone3f(void)
{
	init_shot3f(pos3f(_player()->x, _player()->y, (_player()->z) + 100),
		pos3f(_player()->x + _player()->dx * _weapon()[_player()->weapon_id]
			->range, _player()->y + _player()->dy * _weapon()[_player()
			->weapon_id]->range, _player()->z - ((sin(normalise_between2f(
							posf(-960, 960), posf(-1, 1), _player()->pitch))
					* 1000) * _weapon()[_player()->weapon_id]->range)));
}

void	shoot_touched(int i, int *touched, t_vector3F closest3f)
{
	_player()->shooted.id = _var()->o_player[i].id;
	_player()->shooted.shoot = 1;
	if ((!_var()->o_player[i].is_crouching && closest3f.z < 40)
		|| (_var()->o_player[i].is_crouching && closest3f.z < 165))
		shoot_type(2, i);
	else if ((!_var()->o_player[i].is_crouching && closest3f.z
			< 235) || (_var()->o_player[i].is_crouching
			&& closest3f.z < 315))
		shoot_type(1, i);
	else
		shoot_type(3, i);
	*touched = 1;
	_player()->touched = 1;
	_var()->start_touch = get_clock(_var()->clock);
	_var()->shotanim_start = get_clock(_var()->clock);
	_var()->shot_anim = 1;
	if (_player()->weapon_id != KNIFE)
		init_shot3f(pos3f(_player()->x, _player()->y, _player()->z + 100),
			closest3f);
}

int	is_wall_closest(t_vector2F closest)
{
	t_vector3F	tmp;
	float		wall_dist;

	tmp = pos3f(0, 0, 0);
	nearest_wall3d(&tmp);
	wall_dist = one_dist2f(posf(_player()->x, _player()->y),
			posf(tmp.x, tmp.y));
	if (wall_dist > one_dist2f(posf(_player()->x, _player()->y), closest))
		return (1);
	return (0);
}
