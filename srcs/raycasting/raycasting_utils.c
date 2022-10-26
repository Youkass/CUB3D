/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:43:03 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/26 19:31:55 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int intersects(t_circle circle, t_rect rect)
{
	t_vector2F	circle_dist;
	float		corner;

    circle_dist.x = fabs(circle.x - rect.x);
    circle_dist.y = fabs(circle.y - rect.y);

    if (circle_dist.x > (rect.width/2 + circle.radius))
		return (0);
    if (circle_dist.y > (rect.height/2 + circle.radius))
		return (0);

    if (circle_dist.x <= (rect.width/2))
		return (1); 
    if (circle_dist.y <= (rect.height/2))
		return (1);

    corner = pow((circle_dist.x - rect.width/2), 2) + pow((circle_dist.y - rect.height/2), 2);
    return (corner <= (pow(circle.radius, 2)));
}

void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b)
{
	if (b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 3] != -1)
	{
		a->addr[pos_a.y * a->line_length + pos_a.x * 4] = b->addr[(pos_b.y *b->line_length)  + (pos_b.x * 4)];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 1] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 1];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 2] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 2];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 3] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 3];
	}
}

void	ft_put_pixel_color(t_data *a, char color[4], int x, int y)
{
	if (color[3] != -1)
	{
		a->addr[y * a->line_length + x * 4] = color[0];
		a->addr[(y * a->line_length + x * 4) + 1] = color[1];
		a->addr[(y * a->line_length + x * 4) + 2] = color[2];
		a->addr[(y * a->line_length + x * 4) + 3] = color[3];
	}
}
