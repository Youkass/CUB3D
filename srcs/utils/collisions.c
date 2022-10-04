/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:27:04 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/04 12:35:14 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	detect_neighbors(void)
{
	t_vector2D	it;
	int			n;

	it.x = 1;
	n = 0;
	_player()->hb.hit.x = _player()->x;
	_player()->hb.hit.y = _player()->y;
	while (it.x > -2)
	{
		it.y = 1;
		while (it.y > -2)
		{
			_player()->hb.nb[n] = (t_vector2D){(int)(_player()->x + it.x + 0.5), (int)(_player()->y + it.y + 0.5)};
			it.y--;
			n++;
		}
		it.x--;
	}
}

float	max_f(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	min_f(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int	is_neighbor(t_vector2D pos)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (_player()->hb.nb[i].x == pos.x && _player()->hb.nb[i].y == pos.y)
			return (1);
		i++;
	}
	return(0);
}

t_vector2F	init_potential_dist(int up)
{
	t_vector2F	potential;

	if (up)
	{
		potential.x = _player()->x + (_player()->dx * _player()->move_speed);
		potential.y = _player()->y + (_player()->dy * _player()->move_speed);
	}
	else
	{
		potential.x = _player()->x - (_player()->dx * _player()->move_speed);
		potential.y = _player()->y - (_player()->dy * _player()->move_speed);
	}
	return (potential);
}

/*
-Algorithm that find if in the neighbors of player is there a wall and after
check if that wall is intersect by the circle.
To find that we compute the nearest side of x and y wall and we stock the sub of
xplayer and xwall and yplayer and ywall that are the paralele vector of nearest
wall and center of potential position {position after the deplacement}.
After that we check if the circle and line overlap and if then so we
compute of inverse of the too much overlaping vector {is the vector of center
of circle to the point of the rect inside of circle} and substract this to the
potential value by multiplying it by the overlaping value.

neareast[1] is the segment from center of circle to the point of box {rect} that
is inside the circle.

norm {nearest[1]}  we normalise nearest between 0 and 1 to have the dir vector.

norm {nearest[1]} * overlap is the vector multiply by the scale of the overlap 
segment. So we move the circle in the nearest[1] direction overlap time to stop
overlaping the box.

*/
int	check_neighbor(int up)
{
	int			i;
	int			ret;
	t_vector2F	nearest[2];
	t_vector2F	potential;
	float		overlap;

	ret = 0;
	potential = init_potential_dist(up);
	i = 0;
	while (i < 9)
	{
		if (_player()->hb.nb[i].y >= 0 && _player()->hb.nb[i].x >= 0 && _img()->map[_player()->hb.nb[i].y][_player()->hb.nb[i].x] == '1')
		{
			nearest[0].x = max_f((float)(_player()->hb.nb[i].x - 0.5), min_f(potential.x,(float)_player()->hb.nb[i].x + 0.5));
			nearest[0].y = max_f((float)(_player()->hb.nb[i].y- 0.5), min_f(potential.y,(float)_player()->hb.nb[i].y + 0.5));
			nearest[1].x = nearest[0].x - potential.x;
			nearest[1].y = nearest[0].y - potential.y;
			overlap = _player()->hb.hit.radius - mag(nearest[1]); // calculate magnitude
			if (powf(nearest[1].x, 2) + powf(nearest[1].y, 2) < 0)
				overlap = 0;
			if (overlap > 0)
			{
				potential.x = potential.x - norm(nearest[1]).x * overlap;
				potential.y = potential.y - norm(nearest[1]).y * overlap;
				_player()->x = potential.x;
				_player()->y = potential.y;
				ret = 1;
			}
		}
		i++;
	}
	return (ret);
}
