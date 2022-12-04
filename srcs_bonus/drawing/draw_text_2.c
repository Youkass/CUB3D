/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:11:29 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

int	is_allow_alpha(char c)
{
	if ((c < '0' || c > '9') && (c < 'A' && c > 'Z') && c != '_' && c != ' '
		&& c != '(' && c != ')' && c != ':' && c != '.' && c != '\'' && c
		!= '-')
		return (0);
	return (1);
}

char	char_up(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

void	draw_text(char *text, t_vector2D pos, char color[4])
{
	t_vector2D	tmp;
	int			i;
	int			len;

	tmp = pos;
	i = 0;
	len = ft_strlen(text);
	while (i < len)
	{
		if (is_allow_alpha(text[i]))
			ft_draw_char(*_img(),
				_image()->alpha[(int)char_up(text[i])], tmp, color);
		tmp.x += 42;
		if (tmp.x + 42 >= WIN_W)
		{
			tmp.x = pos.x;
			tmp.y += 42;
		}
		if (tmp.y + 42 > WIN_H)
			return ;
		i++;
	}
}

t_data	ft_draw_char(t_data big, t_data lil, t_vector2D pos, char color[4])
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;

	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	if (pos.x + lil.w > big.w || (pos.y) + lil.h > big.h)
		return (big);
	while (it.y < lil.h)
	{
		it.x = 0;
		while (it.x < lil.w)
		{
			if (lil.addr[it.x * 4 + it.y * lil.line_length] < 0)
				draw_pixel_color(&big, rel_pos[0], color);
			rel_pos[0].x += 4;
			pos.x++;
			it.x++;
		}
		pos.y++;
		rel_pos[0].y = pos.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y++;
	}
	return (big);
}

int	ft_chk_draw(t_vector2D *it, t_vector2D p, t_data lil, t_vector2D scale)
{
	t_data	big;

	big = *_img();
	*it = (t_vector2D){0, 0};
	if (p.x + lil.w > big.w || (p.y) + lil.h > big.h)
		return (1);
	if (scale.x > 20 || scale.y > 20)
		return (1);
	return (0);
}
