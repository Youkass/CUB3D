/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:10:14 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 20:53:27 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
The following function will give us the right size for the elements in the 2D 
map.
===============================================================================
*/
void	ft_find_wall_scale(void)
{
	if (_var()->nx != 1 || _var()->ny != 1)
		ft_black_hole(22);
	_var()->scale = 11;
	_var()->half_scale = _var()->scale / 2;
	_var()->half_scale_offset = _var()->half_scale + (MINIMAP_SIZE - WIN_W)
	- _player()->x * _var()->scale - 350;
}

/*
===============================================================================
Here we're giving to each objects in the cartesian plan an ID 
===============================================================================
*/
void	ft_give_id(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < _var()->map_height)
	{
		j = 0;
		while (j < _var()->map_width)
		{
			if (_var()->coord_map[i][j].c == 'Z')
				_var()->coord_map[i][j].id = VOID;
			if (_var()->coord_map[i][j].c == '1')
				_var()->coord_map[i][j].id = WALL;
			if (_var()->coord_map[i][j].c == '0')
				_var()->coord_map[i][j].id = MAP;
			if (_var()->coord_map[i][j].c == 'P')
				_var()->coord_map[i][j].id = PLAYER;
			++j;
		}
		++i;
	}
}
