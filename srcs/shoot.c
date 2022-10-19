/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:37:47 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/19 17:32:43 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

//int	is_shoot_touch(t_vector2F a, t_vector2F b, t_vector2F c, float r)
//{
//	float		r2;
//	float		len;
//	t_vector2F	n;
//	float		dist;
//	float		index;

//	a = (t_vector2F){a.x - c.x, a.y - c.y};
//	b = (t_vector2F){b.x - c.x, b.y - c.y};
//	r2 = r * r;
//	if (a.x * a.x + a.y * a.y <= r2)
//		return (1);
//	if (b.x * b.x + b.y * b.y <= r2)
//		return (1);
//	len = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
//	n.x = b.y - a.y;
//	n.y = a.x - b.x;
//	dist = n.x * a.x + n.y * a.y;
//	dist = dist * dist;
//	if (dist > len * r2)
//		return (0);
//	index = (a.x*(a.x - b.x) + a.y*(a.y - b.y));
//	if (index < 0)
//		return (0);
//	if (index > len)
//		return (0);
//	return (1);
//}

//void	shoot(void)
//{
//	int	i;

//	i = 0;
//	while (i < _img()->nb_player)
//	{
//		if (is_shoot_touch((t_vector2F){_player()->x, _player()->y},
//			(t_vector2F){_player()->x + (_player()->dx * 150), _player()->y
//			+ (_player()->dy * 150)}, (t_vector2F){_server()->player_data[i].x,
//			_server()->player_data[i].y}, 1))
//		{
//			printf("hey\n");
//			_server()->player_data[i].death_start = get_clock(_var()->clock);
//			_server()->player_data[i].is_dead = 1;
//			_server()->player_data[i].death_n = 0;
//		}
//		i++;
//	}
//}

// FAIRE LES SHOOTS COTE SERVEUR