/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:26 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/24 14:21:08 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_allow_alpha(char c)
{
	if ((c < '0' || c > '9') && (c < 'A' && c > 'Z') && c != '_' && c != ' '
	&& c != '(' && c != ')' && c != ':' && c != '.' && c != '\'')
		return (0);
	return (1);
}

char	char_up(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

void	draw_text(char *text, t_vector2D pos, t_data *img)
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
		{
			ft_put_image_to_image(*img, _var()->alpha[(int)char_up(text[i])], tmp);
		}
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

t_data	create_text_img(char *text)
{
	t_vector2D	pos;
	t_data		new;
	int			i;
	int			len;

	i = 0;
	pos = (t_vector2D){10, 10};
	len = ft_strlen(text);
	new.width = (len * 42) + 20;
	new.height = 66;
	new.img = mlx_new_image(_mlx()->mlx, new.width, new.height);
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
	while (i < len)
	{
		if (is_allow_alpha(text[i]))
			ft_put_image_to_image(new, _var()->alpha[(int)char_up(text[i])], pos);
		pos.x += 42;
		i++;
	}
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
	return (new);
}

void	draw_rectange(t_vector2D a, t_vector2D size, t_data *img, char color[4])
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
			ft_put_pixel_color(img, color, a.x, a.y);
			j++;
			a.y++;
		}
		i++;
		a.x++;
	}
}
