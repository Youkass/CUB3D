/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:34:23 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/14 16:47:07 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_health(t_vector2D	a)
{
	int		i;
	char 	*str;

	str = ft_strjoin(ft_itoa(_player()->health), "HP");
	i = 0;
	draw_rectange(a, pos(102, 22), WHITE);
	while (i < _player()->health)
	{
		draw_rectange(pos(a.x + 1 + i, a.y + 1), pos(1, 20), RED);
		i++;
	}
	draw_text_scale(str, pos(a.x + ft_strlen(str) * (42 / 4), a.y + 5), pos(4, 4), WHITE);
}