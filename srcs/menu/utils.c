/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:06:23 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/04 18:19:14 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	ft_incr(int *i, int *j)
{
	*i += 1;
	*j += 1;
}

t_data	ft_put_sprt_to_img(t_data l, t_vector2D p, t_vector2D sp, t_vector2D s)
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;
	t_vector2D	save;

	save = p;
	if (ft_chk_sprite(&it, p, s, rel_pos))
		return (*_img());
	while (it.y < s.y)
	{
		it.x = 0;
		p.x = save.x;
		while (it.x < s.x)
		{
			if (s.x + it.x < (*_img()).w)
				draw_pixel(_img(), l, (t_vector2D){(sp.x + it.x),
					it.y + sp.y}, rel_pos[0]);
			rel_pos[0].x += 4;
			ft_incr(&p.x, &it.x);
		}
		ft_incr(&p.y, &it.y);
		rel_pos[0].y = p.y * (*_img()).line_length;
		rel_pos[0].x = rel_pos[1].x;
	}
	return (*_img());
}

void	draw_pixel_color(t_data *big, t_vector2D rel_pos, char pix[4])
{
	big->addr[rel_pos.x + rel_pos.y] = pix[0];
	big->addr[rel_pos.x + rel_pos.y + 1] = pix[1];
	big->addr[rel_pos.x + rel_pos.y + 2] = pix[2];
	big->addr[rel_pos.x + rel_pos.y + 3] = pix[3];
}

void	draw_vertical_line(t_data *img, t_vector2D pos, int h)
{
	t_vector2D	rel_pos[2];
	int			i;
	int			n;
	static char	color[2][4] = {{146, 122, 20, 0}, {103, 86, 14, 0}};

	i = 0;
	n = 0;
	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * img->line_length};
	rel_pos[1] = rel_pos[0];
	while (i < h)
	{
		if (i == h / 2)
			n++;
		draw_pixel_color(img, rel_pos[0], color[n]);
		pos.y++;
		rel_pos[0].y = pos.y * img->line_length;
		i++;
	}
}

void	draw_bar_fill(void)
{
	int	i;

	i = 0;
	while (i < (int)(_menu()->s_bar * BAR_INC))
	{
		draw_vertical_line(_img(), (t_vector2D){819 - OFFSET_X + 42
			+ i, 443 - OFFSET_Y + 36}, 27);
		i++;
	}
	i = 0;
	while (i < (int)(_menu()->m_bar * BAR_INC))
	{
		draw_vertical_line(_img(), (t_vector2D){819 - OFFSET_X + 42
			+ i, 542 - OFFSET_Y + 36}, 27);
		i++;
	}
}
