/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:20:26 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/22 17:47:51 by denissereno      ###   ########.fr       */
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
			printf("%d %c\n", i, text[i]);
			printf("%d\n", tmp.x);
			ft_put_image_to_image(*img, _var()->alpha[(int)char_up(text[i])], tmp);
		}
		tmp.x += 42;
		//if (tmp.x + 42 >= WIN_W)
		//{
		//	tmp.x = pos.x;
		//	tmp.y += 42;
		//}
		//if (tmp.y + 42 > WIN_H)
		//	return ;
		i++;
	}
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