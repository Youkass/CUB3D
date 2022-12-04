/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"
/*
===============================================================================
this is the function that will draw our player on the 2D map.

we need to use a flag for the first drawing, because we're getting the player
position from the cartesian plan, then, we'll move our player directly by
the keyhooks functions {see key_hooks.c}, modifying the position by its
singleton.
===============================================================================
*/

t_vector2D	ft_first_vector(void)
{
	t_vector2D	vector;

	vector.x = (_player()->x * (float)_var()->scale)
		+ _var()->half_scale_offset;
	vector.y = (_player()->y * (float)_var()->scale) + _var()->half_scale;
	return (vector);
}

t_vector2D	ft_scnd_vector(void)
{
	t_vector2D	vector;

	vector.x = ((_player()->x * (float)_var()->scale)
			+ _var()->half_scale_offset) + _player()->dx * 10;
	vector.y = (_player()->y * (float)_var()->scale)
		+ (_player()->dy * 10) + _var()->half_scale;
	return (vector);
}

/*
===============================================================================
fonction a ajouter dans un fichier utils_draw_circle.c //TODO
===============================================================================
*/

int	ft_return_xp(t_obj *player, t_obj *my_player)
{
	float	pos_x;

	if (_player()->x - MINIMAP_SIZE < 0)
		pos_x = _player()->x + 1.5;
	else
		pos_x = (float)MINIMAP_SIZE + 1.5 - ((int)_player()->x - _player()->x);
	player->hb.hit.pos.x = player->x;
	(void)my_player;
	return ((int)(pos_x
		* _var()->scale));
}

int	ft_return_yp(t_obj *player, t_obj *my_player)
{
	float	pos_y;

	if (_player()->y - MINIMAP_SIZE < 0)
		pos_y = _player()->y + 1.5;
	else
		pos_y = (float)MINIMAP_SIZE + 1.5 - ((int)_player()->y - _player()->y);
	(void)my_player;
	player->hb.hit.pos.y = player->y;
	return ((int)(pos_y * _var()->scale));
}

float	ft_return_radius(t_obj *player)
{
	return ((player->hb.hit.r) * _var()->scale);
}
