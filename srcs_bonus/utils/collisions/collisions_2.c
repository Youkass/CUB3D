/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:04:50 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

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

void	ft_compute_nb(float overlap)
{
	_nb()->potential.x = _nb()->potential.x
	- norm(_nb()->nearest[1]).x * overlap;
	_nb()->potential.y = _nb()->potential.y
	- norm(_nb()->nearest[1]).y * overlap;
	_player()->x = _nb()->potential.x;
	_player()->y = _nb()->potential.y;
	_nb()->ret = 1;
}

t_vector2F	ft_cal_nearest(int i)
{
	t_vector2F	ret;
	float		help;

	help = min_f(_nb()->potential.x, (float)_player()->hb.nb[i].x + 0.5);
	ret.x = max_f((float)(_player()->hb.nb[i].x - 0.5), help);
	help = min_f(_nb()->potential.y, (float)_player()->hb.nb[i].y + 0.5);
	ret.y = max_f((float)(_player()->hb.nb[i].y - 0.5), help);
	return (ret);
}
