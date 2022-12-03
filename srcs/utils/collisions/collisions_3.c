/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:04:50 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 16:05:38 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

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
