/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:07:21 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 18:21:36 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Functions that make all button restart to normal state 
(normal, hover or active).
*/
void	restart_button(void)
{
	int	i;

	i = 0;
	while (i < 4)
		_menu()->s_state[i++].state = 0;
	i = 0;
	while (i < 7)
		_menu()->o_state[i++].state = 0;
}

/*
-Check if position is in the hitbox given in parameter.
*/
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos)
{
	if (pos.x >= hitbox[0].x && pos.x <= hitbox[1].x
		&& pos.y >= hitbox[0].y && pos.y <= hitbox[2].y)
	{
		return (1);
	}
	return (0);
}

/*
-Draw a pixel if lil image on big image at rel_pos coordinate on the big from
the it coordinate of the lil image.
*/
void	draw_pixel(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos)
{
	if (lil.addr[it.x * 4 + it.y * lil.line_length + 3] != -1)
	{
		big->addr[rel_pos.x + rel_pos.y] = lil.addr[it.x * 4
			+ it.y * lil.line_length];
		big->addr[rel_pos.x + rel_pos.y + 1] = lil.addr[it.x * 4
			+ it.y * lil.line_length + 1];
		big->addr[rel_pos.x + rel_pos.y + 2] = lil.addr[it.x * 4
			+ it.y * lil.line_length + 2];
		big->addr[rel_pos.x + rel_pos.y + 3] = lil.addr[it.x * 4
			+ it.y * lil.line_length + 3];
	}
}

void	draw_pixel_create(t_data *big, t_data lil, t_vector2D it, t_vector2D r)
{
	big->addr[r.x + r.y] = lil.addr[it.x * 4
		+ it.y * lil.line_length];
	big->addr[r.x + r.y + 1] = lil.addr[it.x * 4
		+ it.y * lil.line_length + 1];
	big->addr[r.x + r.y + 2] = lil.addr[it.x * 4
		+ it.y * lil.line_length + 2];
	big->addr[r.x + r.y + 3] = lil.addr[it.x * 4
		+ it.y * lil.line_length + 3];
}

void	ft_init_rel2(t_vector2D *rel_pos, t_vector2F *it, t_vector2D p)
{
	t_data	big;

	big = *_img();
	rel_pos[0] = (t_vector2D){p.x * 4, p.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	*it = (t_vector2F){0, 0};
}
