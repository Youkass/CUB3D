/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:26 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/11 18:17:05 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

//char	*colo(int r, int g, int b)
//{
//	return ((char[4]){127, 0, 255, 0});
//	return ((char[4]){b, g, r, 0});
//}

int	is_allow_alpha(char c)
{
	if ((c < '0' || c > '9') && (c < 'A' && c > 'Z') && c != '_' && c != ' '
	&& c != '(' && c != ')' && c != ':' && c != '.' && c != '\'' && c != '-')
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
			ft_draw_char(*_img(), _image()->alpha[(int)char_up(text[i])], tmp, color);
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
	if (pos.x + lil.w > big.w
	|| (pos.y) + lil.h > big.h)
		return (big);
	(void)color;
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

t_data	ft_draw_char_scale(t_data big, t_data lil, t_vector2D p, t_vector2D scale, char color[4])
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;

	rel_pos[0] = (t_vector2D){p.x * 4, p.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	if (p.x + lil.w > big.w
	|| (p.y) + lil.h > big.h)
		return (big);
	if (scale.x > 20 || scale.y > 20)
		return (big);
	while (it.y < lil.h)
	{
		it.x = 0;
		while (it.x < lil.w)
		{
			if (lil.addr[it.x * 4 + it.y * lil.line_length] < 0)
				draw_pixel_color(&big, rel_pos[0], color);
			rel_pos[0].x += 4;
			p.x++;
			it.x += scale.x;
		}
		p.y++;
		rel_pos[0].y = p.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y += scale.y;
	}
	return (big);
}

void	draw_text_scale(char *text, t_vector2D pos, t_vector2D scale, char color[4])
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
			ft_draw_char_scale(*_img(), _image()->alpha[(int)char_up(text[i])],
				tmp, scale, color);
		tmp.x += 42 / scale.x;
		if (tmp.x + 42 / scale.x >= WIN_W)
		{
			tmp.x = pos.x;
			tmp.y += 42 / scale.x;
		}
		if (tmp.y + 42 / scale.x > WIN_H)
			return ;
		i++;
	}
}

t_data	create_text_img(char *text, char color[4])
{
	t_vector2D	pos;
	t_data		new;
	int			i;
	int			len;

	i = 0;
	pos = (t_vector2D){10, 10};
	len = ft_strlen(text);
	new.w = (len * 42) + 20;
	new.h = 66;
	new.img = mlx_new_image(_mlx()->mlx, new.w, new.h);
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
	while (i < len)
	{
		if (is_allow_alpha(text[i]))
			ft_draw_char(new, _image()->alpha[(int)char_up(text[i])], pos, color);
		pos.x += 42;
		i++;
	}
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
	return (new);
}

void	draw_rectange(t_vector2D a, t_vector2D size, char color[4])
{
	int	i;
	int	j;
	int	y_tmp;

	i = 0;
	j = 0;
	y_tmp = a.y;
	while (i < size.x)
	{
		j = 0;
		a.y = y_tmp;
		while (j < size.y)
		{
			if (a.x < _img()->w && a.y < _img()->h)
				ft_put_pixel_color(_img(), color, a.x, a.y);
			j++;
			a.y++;
		}
		i++;
		a.x++;
	}
}
