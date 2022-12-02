/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:27:04 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/02 14:03:01 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	ft_if(t_vector2D it)
{
	if ((int)(_player()->x + it.x + 0.5) >= 0 && (int)(_player()->x
				+ it.x + 0.5) < _var()->map_width && (int)(_player()->y + it.y
					+ 0.5) >= 0 && (int)(_player()->y + it.y + 0.5)
			< _var()->map_height && is_wall(_var()->map[(int)
				(_player()->y + it.y + 0.5)][(int)(_player()->x + it.x
					+ 0.5)]))
		return (1);
	return (0);
}

static t_vector2D	ft_cal(t_vector2D it)
{
	t_vector2D	ret;

	ret.x = (int)(_player()->x + it.x + 0.5);
	ret.y = (int)(_player()->y + it.y + 0.5);
	return (ret);
}

void	*detect_neighbors(void)
{
	t_vector2D	it;
	int			n;

	it.x = 1;
	n = 0;
	_player()->hb.hit.pos.x = _player()->x;
	_player()->hb.hit.pos.y = _player()->y;
	while (it.x > -2)
	{
		it.y = 1;
		while (it.y > -2)
		{
			if (ft_if(it))
				_player()->hb.nb[n++] = ft_cal(it);
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
	return (0);
}

static t_vector2F	ft_calf(t_vector2F dir)
{
	t_vector2F	ret;

	ret.y = _player()->y + (dir.y * _player()->move_speed);
	ret.x = _player()->x + (dir.x * _player()->move_speed);
	return (ret);
}

t_vector2F	init_potential_dist(int up)
{
	t_vector2F	potential;
	t_vector2F	dir;

	if (up == 1)
	{
		potential.x = _player()->x + (_player()->dx * _player()->move_speed);
		potential.y = _player()->y + (_player()->dy * _player()->move_speed);
	}
	else if (!up)
	{
		potential.x = _player()->x - (_player()->dx * _player()->move_speed);
		potential.y = _player()->y - (_player()->dy * _player()->move_speed);
	}
	else if (up == 2)
	{
		dir = get_90_angle(-1);
		potential.y = _player()->y + (dir.y * _player()->move_speed);
		potential.x = _player()->x + (dir.x * _player()->move_speed);
	}
	else
	{
		dir = get_90_angle(1);
		potential = ft_calf(dir);
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
		img = ft_malloc(sizeof(t_nb));
	return (img);
}

static void	ft_compute_nb(float overlap)
{
	_nb()->potential.x = _nb()->potential.x
	- norm(_nb()->nearest[1]).x * overlap;
	_nb()->potential.y = _nb()->potential.y
	- norm(_nb()->nearest[1]).y * overlap;
	_player()->x = _nb()->potential.x;
	_player()->y = _nb()->potential.y;
	_nb()->ret = 1;
}

static t_vector2F	ft_cal_nearest(int i)
{
	t_vector2F	ret;
	float		help;

	help = min_f(_nb()->potential.x, (float)_player()->hb.nb[i].x + 0.5);
	ret.x = max_f((float)(_player()->hb.nb[i].x - 0.5), help);
	help = min_f(_nb()->potential.y, (float)_player()->hb.nb[i].y + 0.5);
	ret.y = max_f((float)(_player()->hb.nb[i].y - 0.5), help);
	return (ret);
}

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
