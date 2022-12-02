/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:04:44 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 18:08:35 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	weapons(void)
{
	if (_var()->key[one] && _var()->mode == GAME)
		_player()->weapon_id = 0;
	if (_var()->key[two] && _var()->mode == GAME)
		_player()->weapon_id = 1;
	if (_var()->key[three] && _var()->mode == GAME)
		_player()->weapon_id = 2;
	if (_var()->key[r])
		reload_hook();
}

int	ft_is_wall(t_vector2D pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < _var()->map_width
		&& pos.y < _var()->map_height && is_wall(_var()->map[pos.y][pos.x]))
		return (1);
	return (0);
}
