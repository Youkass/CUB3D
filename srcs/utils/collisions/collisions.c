/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:27:04 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 16:05:17 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	*compute_nb(int i)
{
	float	overlap;

	if (_player()->hb.nb[i].y >= 0 && _player()->hb.nb[i].x >= 0
		&& is_wall(_var()->map[_player()->hb.nb[i].y][_player()->hb.nb[i].x]))
	{
		_nb()->nearest[0] = ft_cal_nearest(i);
		_nb()->nearest[1].x = _nb()->nearest[0].x - _nb()->potential.x;
		_nb()->nearest[1].y = _nb()->nearest[0].y - _nb()->potential.y;
		overlap = _player()->hb.hit.r - mag(_nb()->nearest[1]);
		if (powf(_nb()->nearest[1].x, 2) + powf(_nb()->nearest[1].y, 2) < 0)
			overlap = 0;
		if (overlap > 0)
			ft_compute_nb(overlap);
	}
	return (NULL);
}

int	check_neighbor(int up)
{
	int				i;

	i = 0;
	detect_neighbors();
	_nb()->ret = 0;
	_nb()->potential = init_potential_dist(up);
	while (i < _player()->hb.n)
	{
		compute_nb(i);
		i++;
	}
	return (_nb()->ret);
}

int	circle_circle_col(t_obj *pl)
{
	t_vector2F	dist;
	float		check;

	dist.x = fabsf(_player()->x - pl->x);
	dist.y = fabsf(_player()->y - pl->y);
	check = sqrt((dist.x * dist.x) + (dist.y * dist.y));
	if (check <= 1)
		return (1);
	return (0);
}

static void	ft_player_p(float rad_sum, t_vector2F unit)
{
	_player()->x = _player2()->x + (rad_sum + 0.01) * unit.x;
	_player()->y = _player2()->y + (rad_sum + 0.01) * unit.y;
}

int	circle_collide(void)
{
	t_vector2F	dist;
	t_vector2F	unit;
	float		rad_sum;
	float		length;
	int			i;

	i = 0;
	length = 0;
	while (i < _var()->linked_players)
	{
		if (circle_circle_col(&_var()->o_player[i]))
		{
			dist.x = _player()->x - _player2()->x;
			dist.y = _player()->y - _player2()->y;
			rad_sum = 0.5 + 0.5;
			length = (sqrtf(dist.x * dist.x + dist.y * dist.y) || 1);
			unit.x = dist.x / length;
			unit.y = dist.y / length;
			ft_player_p(rad_sum, unit);
		}
		i++;
	}
	if (length != 0)
		return (1);
	return (0);
}
