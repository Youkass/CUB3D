/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:27:04 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/05 17:54:48 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	*detect_neighbors(void)
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
			if ((int)(_player()->x + it.x + 0.5) >= 0 && (int)(_player()->x + it.x + 0.5) < _img()->map_width
			&& (int)(_player()->y + it.y + 0.5) >= 0 && (int)(_player()->y + it.y + 0.5) < _img()->map_height
			&& _img()->map[(int)(_player()->y + it.y + 0.5)][(int)(_player()->x + it.x + 0.5)] == '1')
				_player()->hb.nb[n++] = (t_vector2D){(int)(_player()->x + it.x + 0.5), (int)(_player()->y + it.y + 0.5)};
			it.y--;
		}
		it.x--;
	}
	_player()->hb.n = n;
	return (NULL);
}

int	is_neighbor(t_vector2D pos)
{
	int	i;

	i = 0;
	while (i < _player()->hb.n)
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

t_nb	*_nb(void)
{
	static t_nb	*img = NULL;
	
	if (!img)
		img = malloc(sizeof(t_nb));
	if (!img)
		return (NULL);
	return (img);
}

void	*compute_nb(int i)
{
	float	overlap;

	if (_player()->hb.nb[i].y >= 0 && _player()->hb.nb[i].x >= 0 && _img()->map[_player()->hb.nb[i].y][_player()->hb.nb[i].x] == '1')
	{
		_nb()->nearest[0].x = max_f((float)(_player()->hb.nb[i].x - 0.5), min_f(_nb()->potential.x,(float)_player()->hb.nb[i].x + 0.5));
		_nb()->nearest[0].y = max_f((float)(_player()->hb.nb[i].y- 0.5), min_f(_nb()->potential.y,(float)_player()->hb.nb[i].y + 0.5));
		_nb()->nearest[1].x = _nb()->nearest[0].x - _nb()->potential.x;
		_nb()->nearest[1].y = _nb()->nearest[0].y - _nb()->potential.y;
		overlap = _player()->hb.hit.radius - mag(_nb()->nearest[1]);
		if (powf(_nb()->nearest[1].x, 2) + powf(_nb()->nearest[1].y, 2) < 0)
			overlap = 0;
		if (overlap > 0)
		{
			_nb()->potential.x = _nb()->potential.x - norm(_nb()->nearest[1]).x * overlap;
			_nb()->potential.y = _nb()->potential.y - norm(_nb()->nearest[1]).y * overlap;
			_player()->x = _nb()->potential.x;
			_player()->y = _nb()->potential.y;
			_nb()->ret = 1;
		}
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
